struct adpcm_state {
    char	index;		/* Index into stepsize table */
};

void adpcm_coder(struct adpcm_state *state)
{
    int index;			/* Current step change index */
    index = state->index;
    state->index = index;
}

struct adpcm_state state;

int main() {
    while(1) {
	adpcm_coder(&state);
    }
}
// Imported from ESBMC regression/cbmc/01_cbmc_Pointer18
// RUN: --unwind 1 --no-unwinding-assertions
// EXPECT: ^VERIFICATION SUCCESSFUL$
