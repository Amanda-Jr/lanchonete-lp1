# Lanchonete

- Struct para prato (id, nome, preço)
Matriz para cardápio (matriz de struct patos)
Struct para pedido (id, pratos[lista de pratos])
Fila para pedidos (quando o pedido está sendo 'preparado')
No pedido o usuário deve informar os pratos e a quantidade

Depois que o usuário fizer o pedido ele deve voltar para o menu.

Os pedidos que tiverem menores quantidades vão estar no início da fila (serão entregues primeiro).

Creio que os pedidos deverão ir para uma lista de pedidos, quando não houverem mais clientes os pedidos deverão ser adicionados a fila de acordo com a quantidade total de itens.