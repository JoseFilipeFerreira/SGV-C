#include "filial.h"
#include <stdbool.h>
#include "glibW.h"
#include <gmodule.h>
#include <string.h>

struct filiais {
    GHashTable* cliCompra;
    GHashTable* prodCompra;
};

typedef struct cliCompra {
    char* cliente;
    GHashTable* prodCli;
    int quantidade[12];
} *CliCompra;

typedef struct prodCompra {
    char* prod;
    GTree* quemComprou;
} *ProdCompra;

typedef struct prodCli {
    char* prod;
    char* cliente;
    bool tipo[2];
    int quantidade[12];
    double total;
} *ProdCli;

static int cmp(const void* a, const void* b, void* c) {
    (void) c;
    return strcmp((char*) a, (char*) b);
}

static ProdCli prodCliInit(char* cliente, char* produto, Tipo tipo, int quantidade, double total, int mes) {
    ProdCli pcl = malloc(sizeof(struct prodCli));
    pcl->prod = malloc(strlen(produto) + 1);
    strcpy(pcl->prod, produto);
    pcl->cliente = cliente;
    memset(pcl->tipo, false, 2 * sizeof(bool));
    memset(pcl->quantidade, 0, 12 * sizeof(int));
    pcl->tipo[tipo] = true;
    pcl->quantidade[mes - 1] += quantidade;
    pcl->total = total;
    return pcl;
}

static void prodCliUpdate(ProdCli pcl, Tipo tipo, int quantidade, int mes, double total) {
    pcl->tipo[tipo] = true;
    pcl->quantidade[mes - 1] += quantidade;
    pcl->total += total;
}

static void prodCliDestroy(void* pc) {
    ProdCli pcl = (ProdCli) pc;
    free(pcl->prod);
    free(pcl);
}

static CliCompra cliCompraInit(const char* cliente) {
    CliCompra cc = malloc(sizeof(struct cliCompra));
    cc->cliente = malloc(strlen(cliente) + 1);
    strcpy(cc->cliente, cliente);
    cc->prodCli = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, prodCliDestroy);
    memset(cc->quantidade, 0, 12 * sizeof(int));
    return cc;
}

static void cliCompraUpdate(CliCompra cc, char* produto, Tipo tipo, int quantidade, double total, int mes) {
    ProdCli pcl = g_hash_table_lookup(cc->prodCli, produto);
    cc->quantidade[mes-1] += quantidade;
    if(pcl) 
        prodCliUpdate(pcl, tipo, quantidade, mes, total);
    else {
        pcl = prodCliInit(cc->cliente, produto, tipo, quantidade, total, mes);
        g_hash_table_insert(cc->prodCli, pcl->prod, pcl);
    }
} 

static void cliCompraDestroy(void* c) {
    CliCompra cc = (CliCompra) c;
    g_hash_table_destroy(cc->prodCli);
    free(cc->cliente);
    free(cc);
}

static ProdCompra prodCompraInit(const char* prod, const char* cli) {
    ProdCompra r = malloc(sizeof(struct prodCompra));
    char* cliente = malloc(strlen(cli) + 1);
    strcpy(cliente, cli);
    r->prod = malloc(strlen(prod) + 1);
    strcpy(r->prod, prod);
    r->quemComprou = g_tree_new_full(cmp, NULL, NULL, free);
    g_tree_insert(r->quemComprou, cliente, cliente);
    return r;
} 

static void prodCompraUpdate(ProdCompra r, char* cliente) {
    g_tree_insert(r->quemComprou, cliente, cliente);
}

static void prodCompraDestroy(void* o) {
    ProdCompra r = (ProdCompra) o;
    g_tree_destroy(r->quemComprou);
    free(r);
} 

static gboolean productLetter(gpointer key, gpointer value, gpointer data) {
    char** array = *(char***) data;
    (void) value;
    *array = malloc(strlen((char*) key) + 1);
    strcpy(*(array++), (char*) key);
    *(char***) data = array;
    return FALSE;
}

int produtoQuemComprou(const Filiais f, const char* id, char*** array) {
    ProdCompra p = g_hash_table_lookup(f->cliCompra, id);
    int size;
    char** arrayr;
    size = g_tree_nnodes(p->quemComprou);
    *array = malloc(size * sizeof(char*));
    arrayr = *array;
    g_tree_foreach(p->quemComprou, productLetter, &arrayr);
    return size;
}

Filiais filialInit() {
    Filiais f = malloc(sizeof(struct filiais));
    f->prodCompra = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, prodCompraDestroy);
    f->cliCompra = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, cliCompraDestroy);
    return f;
}

void filialUpdate(Filiais f, Venda v) {
    char* cliente = getClientSale(v);
    char* produto = getProductSale(v);
    ProdCompra pc = g_hash_table_lookup(f->prodCompra, produto);
    CliCompra cc = g_hash_table_lookup(f->cliCompra, cliente);
    if(cc)
        cliCompraUpdate(cc, produto, getTipoSale(v), getQuantSale(v), getTotalSale(v), getMesSale(v));
    else {
        cc = cliCompraInit(cliente);
        cliCompraUpdate(cc, produto, getTipoSale(v), getQuantSale(v), getTotalSale(v), getMesSale(v));
        g_hash_table_insert(f->cliCompra, cc->cliente, cc);
    }
    if(pc)
        prodCompraUpdate(pc, cliente);
    else {
        pc = prodCompraInit(produto, cliente);
        g_hash_table_insert(f->prodCompra, pc->prod, pc);
    }
    free(produto);
    free(cliente);
}

int getClientQuant(const char* id, int mes, const Filiais f) {
    CliCompra p = g_hash_table_lookup(f->cliCompra, id);
    return p->quantidade[mes];
}

int produtosQuantosCompraram(const char* id, Filiais f) {
    ProdCompra p = g_hash_table_lookup(f->prodCompra, id);
    return g_tree_nnodes(p->quemComprou);
}

static int prodCliCmp(const void* a, const void* b) {
    ProdCli aa = *(ProdCli*) a;
    ProdCli bb = *(ProdCli*) b;
    return bb->total - aa->total;
}

static int prodCliCmpQuant(const void* a, const void* b) {
    ProdCli aa = *(ProdCli*) a;
    ProdCli bb = *(ProdCli*) b;
    return bb->quantidade - aa->quantidade;
}

void mergeUpdate(void* key, void* value, void* data) {
    char* ke = (char*) key;
    ProdCli valu = (ProdCli) value;
    GHashTable* dat = (GHashTable*) data;
    ProdCli tmp = g_hash_table_lookup(dat, ke);
    int quants = 0, i;
    for(i = 0; i < 12; i++)
        quants += valu->quantidade[i];
    if(tmp) tmp->total += valu->total; 
    else g_hash_table_insert(dat, key, prodCliInit(valu->cliente, valu->prod, 0, quants, valu->total, 1));
}

int getMaisVendidosCliente(const Filiais f[], const char* id, int N, char*** rrr) {
    GHashTable* merge = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    GHashTableIter r;
    ProdCli prod;
    char* lixo;
    int i, size;
    for(i = 0; i < N; i++) {
        CliCompra cliCompra = g_hash_table_lookup(f[i]->cliCompra, id);
        g_hash_table_foreach(cliCompra->prodCli, mergeUpdate, merge);
    }
    g_hash_table_iter_init(&r, merge);
    i=0;
    size = g_hash_table_size(merge);
    ProdCli array[size];
    *rrr = malloc(sizeof(char*) * 3);
    while(g_hash_table_iter_next(&r, &lixo, &prod))
        array[i++] = prod;
    qsort(array, size, sizeof(ProdCli), prodCliCmp);
    for(i = 0; i < 3 && i < size; i++) {
        (*rrr)[i] = malloc(strlen(array[i]->prod));
        strcpy((*rrr)[i], array[i]->prod);
    }
    g_hash_table_destroy(merge);
    return i;
}

int getMaisCompradosCliente(const Filiais f[], const char* id, int N, char*** rrr) {
    GHashTable* merge = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    GHashTableIter r;
    ProdCli prod;
    char* lixo;
    int i, size;
    for(i = 0; i < N; i++) {
        CliCompra cliCompra = g_hash_table_lookup(f[i]->cliCompra, id);
        g_hash_table_foreach(cliCompra->prodCli, mergeUpdate, merge);
    }
    g_hash_table_iter_init(&r, merge);
    i=0;
    size = g_hash_table_size(merge);
    ProdCli array[size];
    *rrr = malloc(sizeof(char*) * size);
    while(g_hash_table_iter_next(&r, &lixo, &prod))
        array[i++] = prod;
    qsort(array, size, sizeof(ProdCli), prodCliCmpQuant);
    for(i = 0; i < size; i++) {
        (*rrr)[i] = malloc(strlen(array[i]->prod));
        strcpy((*rrr)[i], array[i]->prod);
    }
    g_hash_table_destroy(merge);
    return i;
}

void destroyFilial(Filiais f) {
    g_hash_table_destroy(f->cliCompra);
    g_hash_table_destroy(f->prodCompra);
    free(f);
}

