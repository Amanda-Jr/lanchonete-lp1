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
  int id;
  int **pratos;
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

Nofila *desenfileirar(Fila *f)
{
  if (f->ini == NULL)
  {
    return NULL;
  }
  else if (f->ini == f->fim)
  {
    Nofila *p = f->ini;
    f->ini = NULL;
    f->fim = NULL;

    return p;
  }
  else
  {
    Nofila *p = f->ini;
    f->ini = f->ini->prox;
    f->ini->ant = NULL;
    return p;
  }
}

Prato criar_prato(int id, string nome, double preco)
{
  Prato prato;
  prato.id = id;
  prato.nome = nome;
  prato.preco = preco;

  return prato;
}

// Função com descritor para exibir o cardápio
void exibirCardapio(Prato *listaPratos, int qtdePratos)
{
  for (int i = 0; i < qtdePratos; i++)
  {
    cout << listaPratos[i].id << " - " << listaPratos[i].nome << " | "
         << "R$ " << listaPratos[i].preco << endl;
  }
}

double calcularTotalPedido(Prato *pratos, Pedido pedido)
{
  double total = 0;
  for (int i = 0; i < pedido.num_pratos; i++)
  {
    int id_prato = pedido.pratos[i][0];
    int quantidade = pedido.pratos[i][1];
    total += pratos[id_prato].preco * quantidade;
  }
  return total;
}

void exibirPedidoComTotal(Prato *pratos, Pedido pedido)
{
  cout << "Pedido #" << pedido.id << ":" << endl;
  for (int i = 0; i < pedido.num_pratos; i++)
  {
    int id_prato = pedido.pratos[i][0];
    int quantidade = pedido.pratos[i][1];
    cout << pratos[id_prato].nome << " | R$ " << pratos[id_prato].preco << " x " << quantidade << endl;
  }
  cout << "Total: R$ " << calcularTotalPedido(pratos, pedido) << endl;
}

void adicionarPedidoNaLista(ListaPedidos *lista, int cont_clientes)
{
  Nofila *Nopedido = new Nofila;
  int item;
  cout << "Quantos itens deseja pedir?" << endl;
  cin >> item;

  Nopedido->pedido.num_pratos = item;
  Nopedido->pedido.pratos = new int *[item];

  for (int i = 0; i < item; i++)
  {
    int id_item;
    int quantidade;
    cout << "Qual o numero do item " << i + 1 << " do seu pedido? ";
    cin >> id_item;
    cout << "Quantidade desejada: ";
    cin >> quantidade;

    Nopedido->pedido.pratos[i] = new int[2];
    Nopedido->pedido.pratos[i][0] = id_item - 1;
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

void exibirPedidosNaLista(ListaPedidos *lista, Prato *pratos)
{
  Nofila *atual = lista->inicio;
  while (atual != NULL)
  {
    exibirPedidoComTotal(pratos, atual->pedido);
    atual = atual->prox;
  }
}

void adicionarPedidosNaFila(ListaPedidos *lista, Fila *f)
{
  Nofila *n = lista->inicio;
  int menorQtdeAnterior = 0;

  while (n != NULL)
  {
    Nofila *menor = lista->inicio;
    Nofila *p = lista->inicio;
    int menorQtde = p->pedido.num_pratos;

    while (p->prox != NULL)
    {
      if (p->prox->pedido.num_pratos < menorQtde && p->prox->pedido.num_pratos > menorQtdeAnterior)
      {
        menorQtde = p->prox->pedido.num_pratos;
        menor = p->prox;
      }

      p = p->prox;
    }

    menorQtdeAnterior = menor->pedido.num_pratos;
    enfileirar(f, menor->pedido);

    n = n->prox;
  }
}

void exibirPedidosNaFila(Fila *f, Prato *pratos)
{
  Nofila *atual = f->ini;
  while (atual != NULL)
  {
    exibirPedidoComTotal(pratos, atual->pedido);
    atual = atual->prox;
  }
}

int main()
{
  int qtdePratos = 8;
  bool existe_cliente = true;
  int cont_clientes = 1;

  Prato p1 = criar_prato(1, "Sandubao", 10);
  Prato p2 = criar_prato(2, "Panqueca de Frango", 10);
  Prato p3 = criar_prato(3, "Panqueca de Carne", 10);
  Prato p4 = criar_prato(4, "Pastelao de Frango", 10);
  Prato p5 = criar_prato(5, "Pastelao de Pizza", 10);
  Prato p6 = criar_prato(6, "Milkshake (500 ml)", 7);
  Prato p7 = criar_prato(7, "Refrigerande de lata", 4);
  Prato p8 = criar_prato(8, "Sucos", 6);

  Prato listaPratos[] = {p1, p2, p3, p4, p5, p6, p7, p8};

  Fila *filaPedidos = criarFila();
  ListaPedidos *LP = criarLista();

  cout << "-----Sistema para Lanchonete-----";

  cout << endl
       << endl
       << "------------------------------------------------------------------------------------" << endl
       << "Seja bem-vindo a lanchonete DEZliciosa, delicias que encantam o seu paladar e o seu bolso." << endl
       << "------------------------------------------------------------------------------------";

  while (existe_cliente)
  {
    cout << "\nCliente " << cont_clientes << endl;
    exibirCardapio(listaPratos, 8);

    adicionarPedidoNaLista(LP, cont_clientes);

    string confirm_cliente;
    cout << "Ainda ha cliente? (S/N):";
    cin >> confirm_cliente;

    if (confirm_cliente != "S" && confirm_cliente != "s")
    {
      existe_cliente = false;
    }
    cont_clientes++;
  }

  cout << endl;
  cout << "-----Pedidos na Lista (Demonstrar)-----" << endl;
  exibirPedidosNaLista(LP, listaPratos);

  // Avisar que os pedidos estão prontos de acordo com a lista
  cout << endl;
  cout << "Os pedidos estao sendo preparados!" << endl;

  adicionarPedidosNaFila(LP, filaPedidos);

  cout << "-----Pedidos na Fila-----" << endl;
  exibirPedidosNaFila(filaPedidos, listaPratos);

  cout << endl;

  // Liberar memória alocada para os pratos dos pedidos
  Nofila *atual = LP->inicio;
  while (atual != NULL)
  {
    for (int i = 0; i < atual->pedido.num_pratos; i++)
    {
      delete[] atual->pedido.pratos[i];
    }
    delete[] atual->pedido.pratos;

    atual = atual->prox;
  }

  cout << "Obrigada por comprar na nossa lanchonete, esperamos que tenha tido uma boa experiencia, volte sempre!" << endl;
  delete LP; // Liberar memória da lista de pedidos

  system("pause");

  return 0;
}