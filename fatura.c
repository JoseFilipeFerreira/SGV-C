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
    int mes, quant, filial;
    double pTotal;
    enum Tipo tipo;
    mes = getMesSale(v);
    quant = getQuantSale(v);
    pTotal = quant * getPUnitSale(v);
    tipo = getTipoSale(v);
    filial = getFilialSale(v);
    fat->nVendas[tipo][mes - 1][filial - 1]++;
    fat->total[tipo][mes - 1][filial - 1] += pTotal;
    fat->quant[tipo][mes - 1][filial - 1] += quant;
}

void destroyFact(void* f) {
    FatP fa = (FatP) f;
    free(fa->prod);
    free(fa);
}
