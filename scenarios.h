#ifndef SCENARIOS_H
#define SCENARIOS_H

#include "codes.h"
#include "crypto.h"
#include "galoisFieldExplore.h"
#include <stdio.h>
#include <stdlib.h>


void cryptoScenario();
void exploreScenario(GF_TYPE p, GF_TYPE n);
void addScenario(GF_TYPE p, GF_TYPE n);
void multiplyScenario(GF_TYPE p, GF_TYPE n);

#endif // SCENARIOS_H