#!/bin/sh
# Regenere textures/pack/ a partir des PNG de autretexture/.
#
#   ./tools/gen_textures.sh          # ne recree que ce qui manque
#   ./tools/gen_textures.sh -f       # tout regenerer
#
# VARIANTS controle les declinaisons converties pour chaque famille :
#   VARIANTS="01 05 09" ./tools/gen_textures.sh

set -e

cd "$(dirname "$0")/.."

SRC="autretexture/Horror Textures by Canvas Coven"
OUT="textures/pack"
CONV="python3 tools/png2xpm.py"
VARIANTS="${VARIANTS:-01 09}"
FORCE="$1"

# "dossier source|prefixe des fichiers"
FAMILIES="Dirt|Dirt
Glass|Glass
Grass|Grass
Metal|Metal
Metal grille|Metal_grille
Non-tiled textures|Non-tiled_texture
Patterned stone|Patterned_stone
Sand|Sand
Stone|Stone
Stone tiled bricks|Stone_tiled_bricks
Stone tiles|Stone_tiles
Tiled metal texture|Tiled_metal_texture
Tree bark|Tree_Bark
Unique pattern materials|Unique_pattern_material
Wooden|Wooden"

mkdir -p "$OUT" "$OUT/coins"

echo "$FAMILIES" | while IFS='|' read -r dir prefix; do
	for v in $VARIANTS; do
		png="$SRC/$dir/${prefix}_${v}.png"
		[ -f "$png" ] || continue
		$CONV $FORCE -o "$OUT" "$png"
	done
done

# Frames de piece : mode sprite (le noir pur sert de couleur de transparence)
for png in autretexture/coins/tile*.png; do
	[ -f "$png" ] || continue
	$CONV $FORCE --sprite -o "$OUT/coins" "$png"
done

echo "Pack XPM genere dans $OUT"
