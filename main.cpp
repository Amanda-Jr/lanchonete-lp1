#include <iostream>
#include <stdlib.h>
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
  int **pratos;
  int *quantidades;
  int num_pratos;
};

struct Nofila
{
  Pedido pedido;
  Nofila *prox;
  Nofila *ant;
};

struct Fila
{
  Nofila *ini;
  Nofila *fim;
};

struct ListaPedidos
{
  Nofila *inicio;
  Nofila *fim;
};



Fila *criarFila()
{
  Fila *f = new Fila;
  f->ini = NULL;
  f->fim = NULL;

  return f;
}

ListaPedidos *criarLista()
{
  ListaPedidos *LP = new ListaPedidos;
  LP->inicio = NULL;
  LP->fim = NULL;

  return LP;
}

void enfileirar(Fila *f, Pedido pedido)
{
  Nofila *novo = new Nofila;
  novo->pedido = pedido;
  novo->prox = NULL;
  novo->ant = f->fim;

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
  else {
    Nofila *p = f->ini;
    f->ini = f->ini->prox;
    f->ini->ant = NULL;
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

// Função com descritor para exibir o cardápio
void exibirCardapioDescritor(Prato **cardapio, int lin, int col)
{
  for (int i = 0; i < lin; i++)
  {
    for (int j = 0; j < col; j++)
    {
      cout << cardapio[i][j].id << " - " << cardapio[i][j].nome << " | " << "R$ " << cardapio[i][j].preco << endl;
    }
  }
}

double calcularTotalPedido(Prato **cardapio, Pedido pedido)
{
  double total = 0;
  for (int i = 0; i < pedido.num_pratos; i++)
  {
    int id_prato = pedido.pratos[i][0];
    int quantidade = pedido.pratos[i][1];
    total += cardapio[id_prato / 10][id_prato % 10].preco * quantidade;
  }
  return total;
}

void exibirPedidoComTotal(Prato **cardapio, Pedido pedido)
{
  cout << "Pedido #" << pedido.id << ":" << endl;
  for (int i = 0; i < pedido.num_pratos; i++)
  {
    int id_prato = pedido.pratos[i][0];
    int quantidade = pedido.pratos[i][1];
    cout << cardapio[id_prato / 10][id_prato % 10].nome << " | R$ " << cardapio[id_prato / 10][id_prato % 10].preco << " x " << quantidade << endl;
  }
  cout << "Total: R$ " << calcularTotalPedido(cardapio, pedido) << endl;
}



void adicionarPedidoNaLista(ListaPedidos *lista, Prato ** cardapio, int cont_clientes){
  Nofila *Nopedido = new Nofila;
  int item;
  cout<<"Quantos itens deseja pedir?"<<endl;
  cin >> item;

  Nopedido->pedido.num_pratos = item;
  Nopedido->pedido.pratos = new int *[item];
  Nopedido->pedido.quantidades = new int[item];

  for (int i = 0; i < item; i++)
  {
    int id_item;
    int quantidade;
    cout << "Qual o número do " << i + 1 << "° item do seu pedido? ";
    cin >> id_item;
    cout << "Quantidade desejada: ";
    cin >> quantidade;

    Nopedido->pedido.pratos[i] = new int[2];
    Nopedido->pedido.pratos[i][0] = id_item-1;
    Nopedido->pedido.pratos[i][1] = quantidade;
  }

  Nopedido->pedido.id = cont_clientes;
  Nopedido->ant = NULL;
  Nopedido->prox = NULL;

  if (lista->inicio == NULL)
  {
    lista->inicio = Nopedido;
    lista->fim = Nopedido;
  }
  else
  {
    Nopedido->ant = lista->fim;
    lista->fim->prox = Nopedido;
    lista->fim = Nopedido;
  }

  
}

void exibirPedidosNaLista(ListaPedidos *lista, Prato **cardapio)
{
  Nofila *atual = lista->inicio;
  while (atual != NULL)
  {
    exibirPedidoComTotal(cardapio, atual->pedido);
    atual = atual->prox;
  }
}



int main()
{
  bool existe_cliente = true;
  int cont_clientes = 1;
  Prato** cardapio = criar_cardapio(2, 4);
  popular_cardapio(cardapio);

  Fila *filaPedidos = criarFila();
  ListaPedidos *LP = criarLista();
  ListaPedidos *listaPedidos = new ListaPedidos;

  cout<<"-----Sistema para Lanchonete-----";
   system("color 01");
  cout<< endl << endl <<"------------------------------------------------------------------------------------"<< endl <<"Seja bem-vindo a lanchonete DEZliciosa, delicias que encantam o seu paladar e o seu bolso." << endl<< "------------------------------------------------------------------------------------";


  while (existe_cliente)
  {
    cout<<"\nCliente "<<cont_clientes<<endl;
    exibirCardapioDescritor(cardapio, 2, 4);

    // Pedir pedido 
    Pedido novoPedido;
    enfileirar(filaPedidos, novoPedido);

    adicionarPedidoNaLista(LP, cardapio, cont_clientes);

    string confirm_cliente;
    cout<<"Ainda há cliente? (S/N):";
    cin>>confirm_cliente;

    if(confirm_cliente != "S" && confirm_cliente != "s") {
      existe_cliente = false;
    }
    cont_clientes++;
  }
  cout<<"\nOs pedidos estão sendo preparados!" << endl;
  // Avisar que os pedidos estão prontos de acordo com a lista
  cout << "Pedidos na Lista:" << endl;
  exibirPedidosNaLista(listaPedidos, cardapio);

   // Liberar memória alocada para os pratos dos pedidos
  Nofila *atual = LP->inicio;
  while (atual != NULL)
  {
    for (int i = 0; i < atual->pedido.num_pratos; i++)
    {
      delete[] atual->pedido.pratos[i];
    }
    delete[] atual->pedido.pratos;
    delete[] atual->pedido.quantidades;
    atual = atual->prox;
  }
  system("color 01");
  cout<< "Obrigada por comprar na nossa lanchonete, esperamos que tenha tido uma boa experiência,  volte sempre!";
  delete LP;            // Liberar memória da lista de pedidos
  delete[] cardapio[0]; // Liberar memória do cardápio
  delete[] cardapio[1];
  delete[] cardapio;


  system("pause");

  return 0;
}