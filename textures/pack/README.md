# Pack de textures XPM

La MiniLibX ne sait charger que du XPM (`mlx_xpm_file_to_image`), or les packs
de `autretexture/` sont livres en PNG. Ce dossier contient leur conversion.

- `*.xpm` — murs 64x64 (2 declinaisons par famille du pack *Horror Textures by
  Canvas Coven*), conversion sans perte.
- `coins/*.xpm` — 48 frames de piece 32x32, converties en mode `--sprite` : les
  pixels transparents deviennent noir pur (`#000000`), la valeur que le rendu de
  sprites traite comme transparente.

## Utiliser une texture dans une map

```
NO ./textures/pack/stone_tiled_bricks_01.xpm
SO ./textures/pack/stone_tiled_bricks_09.xpm
WE ./textures/pack/wooden_01.xpm
EA ./textures/pack/patterned_stone_01.xpm
```

Maps de demonstration : `maps/pack_horror.cub`, `maps/pack_nature.cub`,
`maps/pack_industrial.cub`.

```sh
make && ./cub3D maps/pack_horror.cub
```

Les frames de `coins/` servent aux sprites animes de la partie bonus, voir
`BONUS.md` :

```sh
make bonus && ./cub3D_bonus maps/pack_coins.cub
```

## Regenerer / convertir autre chose

```sh
make textures                       # ne genere que ce qui manque
make textures-re                    # tout regenerer
VARIANTS="01 05 09 13" ./tools/gen_textures.sh   # plus de declinaisons

# une texture precise, a la main
python3 tools/png2xpm.py "autretexture/Horror Textures by Canvas Coven/Sand/Sand_12.png" -o textures/pack/
```

`tools/png2xpm.py` n'utilise que la stdlib Python 3 (aucune dependance a
installer sur la VM). Options utiles : `--sprite` (transparence -> noir pur),
`--max-colors N` (quantifie la palette, fichiers bien plus legers),
`-f` (ecrase l'existant).

## Contraintes a respecter

- Le raycaster fait `tex_y & (tex->height - 1)` : la **hauteur doit etre une
  puissance de 2** (64, 128...). Tout le pack est en 64x64, les pieces en 32x32.
- Le parseur XPM de la MiniLibX n'utilise une table directe que si
  `chars-per-pixel <= 2` ; le script s'y tient toujours (1 caractere jusqu'a
  92 couleurs, 2 au-dela, plafond de 8464 couleurs).

Textures d'origine : *Horror Textures* par Canvas Coven.
