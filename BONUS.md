# Partie bonus

Binaire separe, sources separees : le mandatory n'est pas touche.

```sh
make            # cub3D          (mandatory, inchange)
make bonus      # cub3D_bonus    (sprites animes, minimap, souris, collisions)
./cub3D_bonus maps/pack_coins.cub
```

Tout le bonus vit dans `srcs/bonus/*_bonus.c` + `includes/cub3d_bonus.h`.

## Ce qui est fait

| Bonus | Ou |
| --- | --- |
| Sprites animes | `parse_sprites_bonus.c`, `sprite_bonus.c`, `sprite_draw_bonus.c` |
| Minimap | `minimap_bonus.c`, `minimap_draw_bonus.c` |
| Rotation a la souris | `mouse_bonus.c` |
| Collisions murs | `move_bonus.c` |

**Pas fait** : les portes qui s'ouvrent et se ferment.

## Format de map bonus

Deux ajouts par rapport au mandatory :

- `2` dans la grille : une case de sol qui porte un sprite. Le mandatory refuse
  ce caractere, c'est normal — une map avec des `2` ne se lance qu'avec
  `cub3D_bonus`.
- `SP <prefixe>` (optionnel) : prefixe des frames d'animation. Les fichiers
  charges sont `<prefixe>000.xpm`, `<prefixe>001.xpm`... jusqu'a ce qu'il en
  manque un (64 max). Sans `SP`, le prefixe par defaut est
  `./textures/pack/coins/tile`.

```
NO ./textures/pack/stone_tiled_bricks_01.xpm
SO ./textures/pack/stone_tiled_bricks_09.xpm
WE ./textures/pack/wooden_01.xpm
EA ./textures/pack/patterned_stone_01.xpm
SP ./textures/pack/coins/tile

F 38,32,30
C 12,10,12

111111111111111111111111
100020000000000000020001
...
```

Le meme prefixe marche pour les pieges deja presents dans le repo :
`SP ./textures/bear_trap` charge `bear_trap000.xpm` a `bear_trap003.xpm`.

## Details d'implementation

- **Transparence** : le noir pur `#000000` est la couleur de transparence des
  frames. `tools/png2xpm.py --sprite` s'en charge a la conversion et decale les
  pixels noirs *opaques* en `#000001` pour qu'ils restent visibles.
- **Occlusion** : `render_bonus.c` remplit `data->z_buffer[x]` avec la distance
  perpendiculaire du mur touche par chaque colonne. Un sprite n'est dessine sur
  une colonne que si sa profondeur y est inferieure : il disparait correctement
  derriere les murs.
- **Ordre de dessin** : les sprites sont tries du plus loin au plus proche a
  chaque frame (`sort_sprites`).
- **Taille et position** : un sprite fait une demi-case de haut et repose au
  sol, donc son sommet tombe pile sur l'horizon (hauteur de camera = 0.5).
- **Animation** : une frame d'animation tous les `ANIM_DELAY` (3) rendus.
- **Collisions** : le joueur a un rayon (`WALL_PAD`), et chaque axe est teste
  separement pour glisser le long des murs au lieu de se bloquer.

## Verifie

- `make` et `make bonus` compilent en `-Wall -Wextra -Werror` (gcc, Ubuntu ARM64).
- Les quatre maps `maps/pack_*.cub` tournent sans erreur.
- Le mandatory refuse `pack_coins.cub` (`SP` + `2`), comme attendu.
- Les cas d'erreur restent geres : texture manquante, map ouverte, pas de joueur.
