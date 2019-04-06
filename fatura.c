#include "fatura.h"

struct faturacaoProd {
    char* prod;
    int nVendas[2][12][3];
    double total[2][12][3];
    int quant[3];
};

FatP initFatP(Venda p) {
    FatP f = malloc(sizeof(struct faturacaoProd));
    f->prod = getProductSale(p);
    memset(f->nVendas, 0, 2 * 12 * 3 * sizeof(int));
    memset(f->total, 0, 2 * 12 * 3 * sizeof(double));
    memset(f->quant, 0, 3 * sizeof(int));
    mkFatura(f, p);
    return f;
}

void mkFatura(FatP fat, Venda v) { 
    int mes, quant;
    Filial filial;
    Tipo tipo;
    mes = getMesSale(v);
    quant = getQuantSale(v);
    tipo = getTipoSale(v);
    filial = getFilialSale(v);
    fat->nVendas[tipo][mes - 1][filial]++;
    fat->total[tipo][mes - 1][filial] += quant * getPUnitSale(v);
    fat->quant[filial] += quant;
}

FatP cloneFat(FatP a) {
    FatP f = malloc(sizeof(struct faturacaoProd));
    f->prod = malloc(strlen(a->prod) + 1);
    strcpy(f->prod, a->prod);
    memcpy(f->total, a->total, 2 * 12 * 3 * sizeof(double));
    memcpy(f->quant, a->quant, 3 * sizeof(int));
    memcpy(f->nVendas, a->nVendas, 2 * 12 * 3 * sizeof(int));
    return f;
}

double getFatMesFilial(FatP f, Tipo tipo, Filial filial, int mes) {
    if(filial == ALL) 
        return f->total[tipo][mes-1][0] + f->total[tipo][mes-1][1] + f->total[tipo][mes-1][2];
    return f->total[tipo][mes-1][filial];
}

int getQuantMesFilial(FatP f, Filial filial) {
    if(filial == ALL) 
        return f->quant[0] + f->quant[1] + f->quant[2];
    return f->quant[filial];
}

int getNVendasFatura(FatP f, int mes, Filial filial, Tipo tipo) {
    if(filial == ALL) 
        return f->nVendas[tipo][mes][0] + f->nVendas[tipo][mes][1] + f->nVendas[tipo][mes][2];
    return f->nVendas[tipo][mes - 1][filial];
}

int cmpFat(const void* aa, const void* bb) {
    FatP a = *(FatP*) aa;  
    FatP b = *(FatP*) bb;  
    return getQuantMesFilial(b, ALL) - getQuantMesFilial(a, ALL);
}

char* faturaGetId(const FatP f) {
    return f->prod;
}

void destroyFact(void* f) {
    FatP fa = (FatP) f;
    free(fa->prod);
    free(fa);
}
