#define MRAND_MAX	0x7fff
#define MULTIPLIER	0x015a4e35
#define INCREMENT	1

int ramd(int *status) {
    *status=(*status)*MULTIPLIER+INCREMENT;
    return ((*status) >> 16 ) & MRAND_MAX;
}

void sramd(int *status, int semilla) {
	*status=semilla;
	ramd(status);
}