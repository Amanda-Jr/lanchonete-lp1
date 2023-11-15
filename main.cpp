#include <iostream>

using namespace std;

struct Prato
{
  int id;
  string nome;
  double preco;
};

struct Pedido
{
  string id;
  Prato *pratos;
};

struct Nofila
{
  Pedido pedido;
  Nofila *prox;
};

struct Fila
{
  Nofila *ini;
  Nofila *fim;
};

Fila *criar_fila()
{
  Fila *f = new Fila;
  f->ini = NULL;
  f->fim = NULL;

  return f;
}

void enfileirar(Fila *f, Pedido pedido)
{
  Nofila *novo = new Nofila;
  novo->pedido = pedido;
  novo->prox = NULL;
  if (f->ini == NULL)
  {
    f->ini = novo;
    f->fim = novo;
  }
  else
  {
    f->fim->prox = novo;
    f->fim = novo;
  }
}

Nofila* desenfileirar(Fila* f) {
  if(f->ini == NULL) {
    return NULL;
  } else if(f->ini == f->fim) {
    Nofila* p = f->ini;
    f->ini = NULL;
    f->fim = NULL;

    return p;
  }
}

Prato **criar_cardapio(int lin, int col)
{
  Prato **cardapio;
  cardapio = new Prato *[lin];
  for (int i = 0; i < lin; i++)
  {
    cardapio[i] = new Prato[col];
  }
  return cardapio;
}

Prato criar_prato(int id, string nome, double preco) {
  Prato prato;
  prato.id = id;
  prato.nome = nome;
  prato.preco = preco;

  return prato;
}

void popular_cardapio(Prato** cardapio) {
  Prato p1 = criar_prato(1, "Sandubão", 10);
  Prato p2 = criar_prato(2, "Panqueca de Frango", 10);
  Prato p3 = criar_prato(3, "Panqueca de Carne", 10);
  Prato p4 = criar_prato(4, "Pastelão de Frango", 10);
  Prato p5 = criar_prato(5, "Pastelão de Pizza", 10);
  Prato p6 = criar_prato(6, "Milkshake (500 ml)", 7);
  Prato p7 = criar_prato(7, "Refrigerande de lata", 4);
  Prato p8 = criar_prato(8, "Sucos", 6);

  Prato pratos[] = {p1, p2, p3, p4, p5, p6, p7, p8};

  int cont = 0;

  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      cardapio[i][j] = pratos[cont];
      cont++;
    }
  }
  
}

void exibir_cardapio(Prato** cardapio) {
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      cout<<cardapio[i][j].id<<" - "<<cardapio[i][j].nome<<" | "<<"R$ "<<cardapio[i][j].preco<<endl;
    }
    
  }
  
}

int main()
{
  bool existe_cliente = true;
  int cont_clientes = 1;
  Prato** cardapio = criar_cardapio(2, 4);
  popular_cardapio(cardapio);

  cout<<"-----Sistema para Lanchonete-----";

  while (existe_cliente)
  {
    cout<<"Cliente "<<cont_clientes<<endl;
    exibir_cardapio(cardapio);
    // Pedir pedido

    string confirm_cliente;
    cout<<"Ainda há cliente? (S/N):";
    cin>>confirm_cliente;

    if(confirm_cliente != "S" && confirm_cliente != "s") {
      existe_cliente = false;
    }
  }
  cout<<"Os pedidos estão sendo preparados!";
  // Avisar que os pedidos estão prontos de acordo com a lista

  system("pause");

  return 0;
}