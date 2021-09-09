#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
// varivaveis globais

struct carrinho
{
    int codProd, nrVenda, qtdComprada;
    char nomeP;
    float totalItens;

} carrinho[3];

struct cadastro_loja
{

    char nomeLoja[100];
    char cnpj[100];
    char ramo[100];
    int cod_loja;

} loja;

struct cadastro_produto
{
    char nome[100];
    char titulo[100];
    int categoria;
    float preco;
    int qtdProduto;
    int cod_p;
    int qtd_min;

} produto[3];

int i;
int qtd_lojas;
int qtd_prod = 0;
int active_loja = 0;
int active_prod = 0;
int escolha_loja;
int cod_pro_compra;
int respProd = 0;
int posicaoProd;
int qtd;
float totalItens;
int total = 0;
int totaL = 0;
int add_prod = 0;
int tmc = 0;

void categorias()
{
    printf("\n___________ Categorias ___________");
    printf("\n1- Internet das coisas");
    printf("\n2- Inteligencia Artificial");
    printf("\n3- Sistemas Ciber-fisicos");
    printf("\n4- Equipamentos para escritorio");
}
int menu_inicial()
{
    int menu;
    printf("\n---------------Menu-------------- \n");
    printf("1 - Entre como Vendedor \n");
    printf("2 - Entre como Comprador \n");
    printf("3 - Sair \n");
    printf("Digite..: ");
    scanf("%d", &menu);
    printf("\n\n");
    return menu;
}
int menu_vendedor()
{
    int menu = 0;
    printf("-----------Menu Vendedor--------- \n");
    if (active_loja)
    {
        printf("2 - Exibir lojas \n");
        if (active_prod)
        {
            printf("3 - Novo produto \n");
            printf("4 - Exibir produto \n");
        }
        else
        {
            printf("3 - Cadastrar produto");
        }
    }
    else
    {
        printf("1 - Cadastrar uma loja \n");
        printf("5 - Sair \n");
    }
    printf("\nDigite..: ");
    scanf("%d", &menu);
    printf("\n_______________________________________________\n\n");
    return menu;
}
int menu_comprador()
{
    int menu = 0;

    printf("\n--------------- Comprador -------------- \n");
    printf("\n1- Comprar produto");
    if (respProd)
    {
        printf("\n2- Visualizar Carrinho");
        printf("\n3- Remover produto");
        printf("\n4- Finalizar compra");
    }
    printf("\nSelecione..:");
    scanf("%d", &menu);
    printf("\n_______________________________________________\n\n");
    return menu;
}
void cadastrar_loja()
{
    active_loja = 1;
    printf("---------Cadastrando Loja--------- \n");
    printf("Digite o nome da loja:..:");
    fflush(stdin);
    gets(loja.nomeLoja);
    printf("Digite o CNPJ da loja..:");
    fflush(stdin);
    gets(loja.cnpj);
    printf("Digite o segmento da empresa..:");
    gets(loja.ramo);
}
void exibir_loja()
{
    printf("------------ Dados da loja cadastrada--------------- \n");

    printf("\nNome da loja: %s", loja.nomeLoja);
    printf("\t\tcnpj da loja: %s", loja.cnpj);
    printf("\t\tCodigo da loja: %i ", loja.cod_loja);
    printf("\tRamo: %s", loja.ramo);
    printf("\n\n------------------------------------------\n");
}
void cadastrar_produto()
{
    active_prod = 1;
    printf("\nQuantos produtos deseja criar ?");
    scanf("%i", &qtd_prod);
    totaL = totaL + qtd_prod;

    fflush(stdin);
    for (i = total; i < totaL; i++)
    {
        int p = 1;
        printf("\nNome do produto..:");
        fgets(produto[i].nome, 100, stdin);
        printf("\nTitulo do anuncio..:");
        fgets(produto[i].titulo, 100, stdin);
        categorias();
        printf("\nSelecione uma categoria..:");
        scanf("%i", &produto[i].categoria);
        printf("\nDigite o valor..:");
        scanf("%f", &produto[i].preco);
        fflush(stdin);
        printf("\nDigite a quantidade em estoque..:");
        scanf("%i", &produto[i].qtdProduto);
        printf("\nQuantidade minima necessaria em estoque..:");
        scanf("%i", &produto[i].qtd_min);
        fflush(stdin);
        produto[i].cod_p = produto[i].cod_p + i;
    }
    total = total + i;
}
void exibir_produto()
{

    printf("------------Lista de Produtos--------------- \n");
    for (i = 0; i < totaL; i++)
    {
        printf("produto: %s", produto[i].nome);
        printf("\n\nTitulo: %s", produto[i].titulo);
        printf("Categoria: %i \n", produto[i].categoria);
        printf("Preco..: %.3f\n", produto[i].preco);
        printf("Quantidade do estoque: %i\n", produto[i].qtdProduto);
        printf("Nome da empresa: %s\n", loja.nomeLoja);
        printf("Codigo do produto: %i\n", produto[i].cod_p);
        printf("\n\n_______________________________________________\n");
    }
}
void ProdutoCarrinho(int cpc)
{
    for (i = 0; i < totaL; i++)
    {
        if (cpc == produto[i].cod_p)
        {
            respProd = 1;    // econtrou o produto
            posicaoProd = i; // Posição (índice) onde está o codigo do produto
        }
    }
    if (respProd == 1)
    {

        printf("Quantidade..: ");
        scanf("%d", &qtd);
        if (produto[posicaoProd].qtdProduto >= qtd)
        {

            tmc++;
            // atualiza o estoque
            produto[posicaoProd].qtdProduto = produto[posicaoProd].qtdProduto - qtd;
            totalItens = produto[posicaoProd].preco * qtd;

            carrinho[posicaoProd].nomeP = produto[posicaoProd].nome;
            carrinho[posicaoProd].qtdComprada = qtd;
            carrinho[posicaoProd].codProd = cpc;
            carrinho[posicaoProd].totalItens = totalItens;

            // exibir valor do produto
            printf("___________ Carrinho ___________");
            printf("\nProduto..: %i", cpc);
            printf("\nQuantidade..: %i", qtd);
            printf("\nValor Total do item..: %.2f", totalItens);
        }
        else
        {
            printf("Quantidade indisponivel");
        }
    }
    else
    {

        printf("\n _________Produto nao disponivel_________\n");
    }
}
void listarCarrinho()
{
    printf("_________Carrinho_________");
    for (i = 0; i < totaL; i++)
    {

        printf("\nCodigo produto: %i", carrinho[i].codProd);
        printf("\nQuantidade: %i ", carrinho[i].qtdComprada);
        printf("\nValor: %.2f", carrinho[i].totalItens);
        printf("\n_______________________");
    }
}
int main()
{
// caso queria testar alguma função ( add dentro da primeira estrutura)
voltar:
    switch (menu_inicial())
    {
    menu_vendedor:
    case 1:
        switch (menu_vendedor())
        {
        case 1:
            // Fu1nção que cadastra novas lojas e, em seguida, as exibe
            cadastrar_loja();
            goto voltar;
            break;

        case 2:
            // Função que exibe lojas cadastradas
            exibir_loja();
            goto voltar;
            break;

        case 3:
            // Função que cadastra produtos
            cadastrar_produto();
            goto voltar;
            break;

        case 4:
            exibir_produto();
            goto voltar;
            break;
        default:
            goto voltar;
            break;
        }
    case 2:
    menu_comprador:
        switch (menu_comprador())
        {
        case 1:
            do
            {
                categorias();
                int opP;
                printf("\n\nSelecione..:");
                scanf("%i", &opP);
                switch (opP)
                { // Como posso evitar a repetição do filtro ? R:()
                case 1:
                    printf("\n\n - - - -  Lista de produtos Internet das coisas - - - - -");
                    break;
                case 2:
                    printf("\n\n - - - -  Lista de produtos Inteligencia Artificial - - - - -");
                    break;
                case 3:
                    printf("\n\n - - - -  Lista de produtos Sistemas Ciber-fisicos - - - - -");
                    break;
                case 4:
                    printf("\n\n - - - -  Lista de produtos Equipamentos para escritorio - - - - -");
                    break;
                default:
                    break;
                    // meter um goto voltar para o menu do comprador.s
                }
                for (i = 0; i < totaL; i++)
                {
                    if (produto[i].categoria == opP)
                    {
                        printf("\nNome do produto: %s\n", produto[i].nome);
                        printf("Titulo do produto: %s", produto[i].titulo);
                        printf("Nome da empresa: %s", loja.nomeLoja);
                        printf("\nValor do produto:  %.2f", produto[i].preco);
                        printf("\nEstoque: %i", produto[i].qtdProduto);
                        printf("\nCodigo do produto: %i \n\n", produto[i].cod_p);
                        printf("\n_______________________________________________\n");
                    }
                }
                printf("\nInsira o codigo do produto..:");
                scanf("%i", &cod_pro_compra);
                ProdutoCarrinho(cod_pro_compra);
                printf("\nDeseja adcionar um novo produto\n1-sim 2-nao:");
                scanf("%i", &add_prod);
            } while (add_prod == 1);
            goto menu_comprador;
            break;
        case 2:
            listarCarrinho();
            goto menu_comprador;
            break;
        }
        break;
    default:
        goto voltar;
        break;
    }

    system("pause");
    return 0;
}