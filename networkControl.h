#pragma once

#define NB_ROW 6
#define NB_COL 7

#define POPSIZE             400 
#define NBRITERATIONS       1000
#define NBRBATTLES          25

#define INPUTLAYERSIZE      (NB_COL * NB_ROW)
#define HIDDENLAYER1SIZE    64
#define HIDDENLAYER2SIZE    32
#define OUTPUTLAYERSIZE     NB_COL

#define MUTATEPROB          0.3f
#define MUTATEDELTA         0.4f

#define DEBBUG              false