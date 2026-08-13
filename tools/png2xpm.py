#!/usr/bin/env python3
"""Convertit des PNG en XPM lisibles par la MiniLibX (mlx_xpm_file_to_image).

La MiniLibX ne charge que du XPM. Les packs de `autretexture/` sont en PNG :
ce script fait le pont, sans aucune dependance externe (stdlib uniquement).

Usage:
    ./tools/png2xpm.py source.png destination.xpm
    ./tools/png2xpm.py -o textures/pack/ a.png b.png c.png
    ./tools/png2xpm.py --sprite -o textures/pack/coins autretexture/coins/*.png

Options:
    -o DIR         ecrit les .xpm dans DIR (le nom du fichier est conserve)
    --sprite       les pixels transparents deviennent noir pur (#000000), la
                   couleur que le rendu de sprites traite comme transparente ;
                   les pixels noirs opaques sont decales en #000001
    --max-colors N quantifie la palette a N couleurs max (reduit la taille)
    -f, --force    ecrase un .xpm existant
"""

import argparse
import os
import struct
import sys
import zlib

# Alphabet des symboles XPM : ASCII imprimable prive de '"' et '\' (qui
# casseraient le decoupage par guillemets du parseur mlx) et de l'espace.
ALPHABET = [chr(c) for c in range(33, 127) if chr(c) not in ('"', '\\')]


# --------------------------------------------------------------------------- #
# Decodage PNG
# --------------------------------------------------------------------------- #

def read_chunks(blob):
    if blob[:8] != b'\x89PNG\r\n\x1a\n':
        raise ValueError("ce n'est pas un PNG")
    pos = 8
    while pos < len(blob):
        (length,) = struct.unpack('>I', blob[pos:pos + 4])
        kind = blob[pos + 4:pos + 8]
        data = blob[pos + 8:pos + 8 + length]
        pos += 12 + length
        yield kind, data
        if kind == b'IEND':
            return


def unpack_bits(row, depth, count):
    """Etale une scanline de profondeur < 8 en une valeur par element."""
    out = []
    per_byte = 8 // depth
    mask = (1 << depth) - 1
    for byte in row:
        for k in range(per_byte):
            if len(out) == count:
                return out
            out.append((byte >> (8 - depth * (k + 1))) & mask)
    return out


def unfilter(raw, width, height, bpp, stride):
    """Applique les 5 filtres PNG (RFC 2083) ligne par ligne."""
    out = bytearray(stride * height)
    pos = 0
    for y in range(height):
        ftype = raw[pos]
        pos += 1
        line = bytearray(raw[pos:pos + stride])
        pos += stride
        base = y * stride
        prev = base - stride
        if ftype == 1:
            for i in range(bpp, stride):
                line[i] = (line[i] + line[i - bpp]) & 0xFF
        elif ftype == 2:
            if y:
                for i in range(stride):
                    line[i] = (line[i] + out[prev + i]) & 0xFF
        elif ftype == 3:
            for i in range(stride):
                a = line[i - bpp] if i >= bpp else 0
                b = out[prev + i] if y else 0
                line[i] = (line[i] + ((a + b) >> 1)) & 0xFF
        elif ftype == 4:
            for i in range(stride):
                a = line[i - bpp] if i >= bpp else 0
                b = out[prev + i] if y else 0
                c = out[prev + i - bpp] if (y and i >= bpp) else 0
                p = a + b - c
                pa, pb, pc = abs(p - a), abs(p - b), abs(p - c)
                if pa <= pb and pa <= pc:
                    pr = a
                elif pb <= pc:
                    pr = b
                else:
                    pr = c
                line[i] = (line[i] + pr) & 0xFF
        elif ftype != 0:
            raise ValueError("filtre PNG inconnu: %d" % ftype)
        out[base:base + stride] = line
    return out


def decode_png(path):
    """Retourne (width, height, pixels) ou pixels est une liste de (r,g,b,a)."""
    with open(path, 'rb') as fd:
        blob = fd.read()

    idat = bytearray()
    plte = None
    trns = None
    header = None
    for kind, data in read_chunks(blob):
        if kind == b'IHDR':
            header = struct.unpack('>IIBBBBB', data)
        elif kind == b'PLTE':
            plte = data
        elif kind == b'tRNS':
            trns = data
        elif kind == b'IDAT':
            idat += data

    if header is None:
        raise ValueError('IHDR manquant')
    width, height, depth, ctype, comp, filt, interlace = header
    if interlace:
        raise ValueError('PNG entrelace (Adam7) non supporte')
    if comp or filt:
        raise ValueError('compression/filtrage PNG non standard')

    channels = {0: 1, 2: 3, 3: 1, 4: 2, 6: 4}[ctype]
    bpp = max(1, (channels * depth) // 8)
    stride = (width * channels * depth + 7) // 8
    raw = unfilter(zlib.decompress(bytes(idat)), width, height, bpp, stride)

    pixels = []
    for y in range(height):
        line = raw[y * stride:(y + 1) * stride]
        if depth == 16:
            vals = [line[i] for i in range(0, len(line), 2)]
        elif depth == 8:
            vals = list(line)
        else:
            vals = unpack_bits(line, depth, width * channels)
        for x in range(width):
            v = vals[x * channels:(x + 1) * channels]
            if ctype == 0:
                g = v[0] if depth in (8, 16) else v[0] * 255 // ((1 << depth) - 1)
                pixels.append((g, g, g, 255))
            elif ctype == 2:
                pixels.append((v[0], v[1], v[2], 255))
            elif ctype == 3:
                idx = v[0]
                if plte is None or idx * 3 + 2 >= len(plte):
                    raise ValueError('index de palette hors limites')
                a = trns[idx] if (trns and idx < len(trns)) else 255
                pixels.append((plte[idx * 3], plte[idx * 3 + 1],
                               plte[idx * 3 + 2], a))
            elif ctype == 4:
                g = v[0] if depth in (8, 16) else v[0] * 255 // ((1 << depth) - 1)
                pixels.append((g, g, g, v[1]))
            else:
                pixels.append((v[0], v[1], v[2], v[3]))
    return width, height, pixels


# --------------------------------------------------------------------------- #
# Encodage XPM
# --------------------------------------------------------------------------- #

def apply_alpha(pixels, sprite):
    """Aplati le canal alpha. En mode sprite, le noir pur sert de couleur cle."""
    out = []
    for r, g, b, a in pixels:
        if sprite:
            if a < 128:
                out.append((0, 0, 0))
                continue
            if (r, g, b) == (0, 0, 0):
                out.append((0, 0, 1))
                continue
        out.append((r, g, b))
    return out


def quantize(pixels, max_colors, keep_black):
    """Reduit la palette en rognant les bits de poids faible de chaque canal."""
    for bits in range(8, 0, -1):
        shift = 8 - bits
        if shift:
            step = 255 // ((1 << bits) - 1) if bits > 1 else 255
            mapped = [((r >> shift) * step, (g >> shift) * step,
                       (b >> shift) * step) for r, g, b in pixels]
            if keep_black:
                mapped = [(0, 0, 0) if src == (0, 0, 0) else px
                          for px, src in zip(mapped, pixels)]
        else:
            mapped = list(pixels)
        if len(set(mapped)) <= max_colors:
            return mapped
    return mapped


def c_identifier(path):
    name = os.path.splitext(os.path.basename(path))[0]
    safe = ''.join(ch if (ch.isalnum() or ch == '_') else '_' for ch in name)
    if not safe or safe[0].isdigit():
        safe = 'xpm_' + safe
    return safe


def to_xpm(width, height, pixels, name, max_colors=None, sprite=False):
    flat = apply_alpha(pixels, sprite)
    cap = len(ALPHABET) ** 2
    if max_colors:
        flat = quantize(flat, min(max_colors, cap), sprite)
    palette = sorted(set(flat))
    if len(palette) > cap:
        flat = quantize(flat, cap, sprite)
        palette = sorted(set(flat))
    if len(palette) > cap:
        raise ValueError('trop de couleurs meme apres quantification')

    cpp = 1 if len(palette) <= len(ALPHABET) else 2
    symbols = {}
    for i, color in enumerate(palette):
        if cpp == 1:
            symbols[color] = ALPHABET[i]
        else:
            symbols[color] = ALPHABET[i // len(ALPHABET)] + ALPHABET[i % len(ALPHABET)]

    lines = ['/* XPM */',
             'static char *%s[] = {' % name,
             '/* columns rows colors chars-per-pixel */',
             '"%d %d %d %d",' % (width, height, len(palette), cpp),
             '/* colors */']
    for color in palette:
        lines.append('"%s c #%02X%02X%02X",' % (symbols[color], *color))
    lines.append('/* pixels */')
    for y in range(height):
        row = flat[y * width:(y + 1) * width]
        comma = ',' if y < height - 1 else ''
        lines.append('"%s"%s' % (''.join(symbols[px] for px in row), comma))
    lines.append('};')
    return '\n'.join(lines) + '\n'


# --------------------------------------------------------------------------- #

def convert(src, dst, args):
    if os.path.exists(dst) and not args.force:
        print('skip (existe deja): %s' % dst)
        return True
    try:
        width, height, pixels = decode_png(src)
        body = to_xpm(width, height, pixels, c_identifier(dst),
                      args.max_colors, args.sprite)
    except Exception as err:                      # noqa: BLE001
        print('Error\n%s: %s' % (src, err), file=sys.stderr)
        return False
    os.makedirs(os.path.dirname(os.path.abspath(dst)), exist_ok=True)
    with open(dst, 'w') as fd:
        fd.write(body)
    print('%s -> %s (%dx%d)' % (src, dst, width, height))
    return True


def main():
    parser = argparse.ArgumentParser(description='PNG -> XPM pour la MiniLibX')
    parser.add_argument('inputs', nargs='+')
    parser.add_argument('-o', '--out', help='fichier .xpm ou dossier de sortie')
    parser.add_argument('--sprite', action='store_true',
                        help='transparence -> noir pur (#000000)')
    parser.add_argument('--max-colors', type=int, default=None,
                        help='quantifie la palette (ex: 256)')
    parser.add_argument('-f', '--force', action='store_true')
    args = parser.parse_args()

    if len(args.inputs) > 1 and (not args.out or args.out.endswith('.xpm')):
        parser.error('avec plusieurs entrees, -o doit designer un dossier')

    ok = True
    for src in args.inputs:
        if args.out and args.out.endswith('.xpm'):
            dst = args.out
        else:
            base = os.path.splitext(os.path.basename(src))[0]
            base = base.lower().replace(' ', '_') + '.xpm'
            dst = os.path.join(args.out or os.path.dirname(src), base)
        ok = convert(src, dst, args) and ok
    return 0 if ok else 1


if __name__ == '__main__':
    sys.exit(main())
