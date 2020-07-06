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

ll fast_pow(ll basis, ll exponent, ll modulo) {
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

void make_giant_step(ll basis, ll modulo, vector <pair <ll, ll> > &giant_step) {
	ll step = sqrt(modulo), actual_step = 1LL, aux = 0LL;
	ll number_of_steps = modulo / step + 1LL;
	ll value_of_step = fast_pow(basis, step, modulo);
	giant_step.pb({actual_step, aux});
	
	for(ll i = 1LL; i <= number_of_steps; i++) {
		actual_step = (actual_step * value_of_step) % modulo;
		aux += step;
		giant_step.pb({actual_step, aux});
	}
}

void make_baby_step(ll basis, ll number, ll modulo, vector <pair <ll, ll> > &baby_step) {
	ll number_of_steps = sqrt(modulo) + 1LL, aux = 0LL;
	ll value_of_step = basis, actual_step = number;
	baby_step.pb({actual_step, aux});
	
	for(ll i = 1LL; i <= number_of_steps; i++) {
		actual_step = (actual_step * value_of_step) % modulo;
		aux++;
		baby_step.pb({actual_step, aux});
	}
}

//I assume that an answer exists. REMEMBER that there might not be one.
ll discrete_logarithm(ll basis, ll number, ll modulo) {
	int act_position = 0, act_position2 = 0;
	ll ans = 0LL; 
	vector <pair <ll, ll> >giant_step, baby_step;
	
	make_giant_step(basis, modulo, giant_step);
	make_baby_step(basis, number, modulo, baby_step);
	
	sort(giant_step.begin(), giant_step.end());
	sort(baby_step.begin(), baby_step.end());
	
	do {
		while(giant_step[act_position].f < baby_step[act_position2].f) {
			act_position++;
		}
		
		while(giant_step[act_position].f > baby_step[act_position2].f) {
			act_position2++;
		}
		
		if(giant_step[act_position].f == baby_step[act_position2].f) {
			ans = giant_step[act_position].s - baby_step[act_position2].s;
		}
		
	} while(giant_step[act_position].f != baby_step[act_position2].f);
	
	return (ans % modulo + modulo) % modulo;
}
