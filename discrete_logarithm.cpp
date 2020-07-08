//Author : Michał Traczyk

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int M=1e6+7;
const ll q=7057594037927903;
const ll prime=2137;
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define ios ios_base::sync_with_stdio(0)

ll fastPow(ll basis, ll exponent, ll modulo) {
	ll result = 1LL, aux = basis; 
	
	while(exponent != 0LL) {
		if(exponent % 2LL == 1LL) {
			result = (result * aux) % modulo;
			exponent--;
		} else {
			aux = (aux * aux) % modulo;
			exponent = exponent / 2LL;
		}
	}
	
	return result;
}

void makeGiantStep(ll basis, ll modulo, vector <pair <ll, ll> > &giantStep) {
	ll step = sqrt(modulo), actualStep = 1LL, aux = 0LL;
	ll numberOfSteps = modulo / step + 1LL;
	ll valueOfStep = fastPow(basis, step, modulo);
	giantStep.pb({actualStep, aux});
	
	for(ll i = 1LL; i <= numberOfSteps; i++) {
		actualStep = (actualStep * valueOfStep) % modulo;
		aux += step;
		aux = aux % (modulo - 1LL);
		giantStep.pb({actualStep, aux});
	}
}

void makeBabyStep(ll basis, ll number, ll modulo, vector <pair <ll, ll> > &babyStep) {
	ll numberOfSteps = sqrt(modulo) + 1LL, aux = 0LL;
	ll valueOfStep = basis, actualStep = number;
	babyStep.pb({actualStep, aux});
	
	for(ll i = 1LL; i <= numberOfSteps; i++) {
		actualStep = (actualStep * valueOfStep) % modulo;
		aux++;
		aux = aux % (modulo - 1LL);
		babyStep.pb({actualStep, aux});
	}
}

//I assume that modulo is a prime number, therefore if a basis is a generator
//mod modulo then there is an answer.
ll discreteLogarithm(ll basis, ll number, ll modulo) {
	int actPosition = 0, actPosition2 = 0;
	ll ans = 0LL; 
	vector <pair <ll, ll> >giantStep, babyStep;
	
	makeGiantStep(basis, modulo, giantStep);
	makeBabyStep(basis, number, modulo, babyStep);
	
	sort(giantStep.begin(), giantStep.end());
	sort(babyStep.begin(), babyStep.end());
	
	do {
		while(giantStep[actPosition].f < babyStep[actPosition2].f) {
			actPosition++;
		}
		
		while(giantStep[actPosition].f > babyStep[actPosition2].f) {
			actPosition2++;
		}
		
		if(giantStep[actPosition].f == babyStep[actPosition2].f) {
			ans = giantStep[actPosition].s - babyStep[actPosition2].s;
		}
		
	} while(giantStep[actPosition].f != babyStep[actPosition2].f);
	
	return (ans % (modulo - 1LL) + modulo - 1LL) % (modulo - 1LL);
}
