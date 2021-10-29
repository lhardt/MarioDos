#ifndef RECURSOS_H
#define RECURSOS_H

/**
 * Sempre há a chance de este jogo ser recompilado com um
 * compilador do Windows, que utilize a contrabarra.
 * Nesse caso, o programador só precisa alterar os #DEFINEs
 * da forma CAMINHO_*s.
 */

/* NOTE: a tempo de compilação, strings podem ser concatenadas
 * sem nenhum sinal entre elas. Ex: ("a" "b") gera "ab".
 */

#define CAMINHO_FONTES "resources/fonts/"
#define CAMINHO_FONTE_MENU (CAMINHO_FONTES "SuperMario256.ttf")

#define CAMINHO_FASES "resources/fases/"

#define CAMINHO_IMAGENS "resources/imagens/"
#define CAMINHO_SPRITESHEET (CAMINHO_IMAGENS "sprite_geral.png")

#define CAMINHO_SONS "resources/som/"

#endif /* RECURSOS_H */
