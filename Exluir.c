// Permite excluir um contato da agenda
Contact *delContact(Contact *contact, char *name)
{
    Contact *aux, *anterior = NULL;
    int cont;

    if (contact == NULL)
    {
        printf("Infelizmente não temos contatos!\n");
    }

    for (aux = contact; aux != NULL; aux = aux->next)
    {
        if (strcmp(aux->name, name) == 0)
        {
            
            if (contact == aux)
            {
                contact = aux->next;
            }
            else
            {
                anterior->next = aux->next;
            }
            free(aux);
            cont = 1;
        }
        anterior = aux;
    }
    if (!cont)
    {
        printf("Infelizmente não temos contatos!\n");
    }
    printf("-------------------------------------------------\n");
    printf("O seu novo contato foi excluido com sucesso!\n");
    printf("-------------------------------------------------\n");
    return contact;
}