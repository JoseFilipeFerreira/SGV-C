#include "fatura.h"

struct faturacaoProd {
    char* prod;
    int nVendas[2][12][3];
    double total[2][12][3];
    int quant[3];
};

FatP initFatP(Venda p) {
    FatP f =(FatP) malloc(sizeof(struct faturacaoProd));
    f->prod = getProductSale(p);
    memset(f->total, 0, 2 * 12 * 3 * sizeof(double));
    memset(f->quant, 0, 3 * sizeof(int));
    memset(f->nVendas, 0, 2 * 12 * 3 * sizeof(int));
    mkFatura(f, p);
    return f;
}

void mkFatura(FatP fatr, Venda v) { 
    FatP fat = fatr;
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

double getFatMesFilial(FatP f, Tipo tipo, Filial filial, int mes) {
    if(filial == ALL) 
        return f->total[tipo][mes-1][0] + f->total[tipo][mes-1][1] + f->total[tipo][mes-1][2];
    return f->total[tipo][mes-1][filial];
}

void printFat(FatP a) {
    printf("%s %d\n", a->prod, a->quant[0]+a->quant[1]+a->quant[2]);
}

int getQuantMesFilial(FatP f, Tipo tipo, Filial filial, int mes) {
    if(filial == ALL) 
        return f->quant[0] + f->quant[1] + f->quant[2];
    return f->quant[filial];
}

int getNVendasFatura(FatP f) {
    int i, j, k, r = 0;
    for(i=0; i < 2; i++)
        for(j=0; j < 12; j++)
            for(k=0; k < 3; k++)
                r += f->nVendas[i][j][k];
    return r;
}

int cmpFat(FatP* a, FatP* b) {
   
     return getQuantMesFilial(*b, N, ALL, 1) - getQuantMesFilial(*a, N, ALL, 1);
}

void destroyFact(void* f) {
    FatP fa = (FatP) f;
    free(fa->prod);
    free(fa);
}
