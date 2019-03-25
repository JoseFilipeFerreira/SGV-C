#include "fatura.h"

struct faturacaoProd {
    char* prod;
    int nVendas[2][12][3];
    double total[2][12][3];
    int quant[2][12][3];
};

FatP initFatP(Venda p) {
    FatP f =(FatP) malloc(sizeof(struct faturacaoProd));
    f->prod = getProductSale(p);
    memset(f->total, 0, 2 * 12 * 3 * sizeof(double));
    memset(f->quant, 0, 2 * 12 * 3 * sizeof(int));
    memset(f->nVendas, 0, 2 * 12 * 3 * sizeof(int));
    mkFatura(f, p);
    return f;
}

void mkFatura(FatP fat, Venda v) { 
    int mes, quant;
    Filial filial;
    double pTotal;
    Tipo tipo;
    mes = getMesSale(v);
    quant = getQuantSale(v);
    pTotal = quant * getPUnitSale(v);
    tipo = getTipoSale(v);
    filial = getFilialSale(v);
    fat->nVendas[tipo][mes - 1][filial]++;
    fat->total[tipo][mes - 1][filial] += pTotal;
    fat->quant[tipo][mes - 1][filial] += quant;
}

double getFatMesFilial(FatP f, Tipo tipo, Filial filial, int mes) {
    if(tipo == AL) 
        return f->total[N][filial][mes-1] + f->total[P][filial][mes-1];
    return f->total[tipo][filial][mes-1];
}

int getQuantMesFilial(FatP f, Tipo tipo, Filial filial, int mes) {
    if(tipo == AL) 
        return f->quant[N][filial][mes-1] + f->quant[P][filial][mes-1];
    return f->quant[tipo][filial][mes-1];
}


void destroyFact(void* f) {
    FatP fa = (FatP) f;
    free(fa->prod);
    free(fa);
}
