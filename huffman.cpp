#include "huffman.hpp"
#include "arbbin.hpp" 
#include <utility>

nat get_cont(vector<nat>&v){
//Compta els elements repetits i els elimina del vector
	nat aux_valor=v[0];
	nat i=0;
	int cont=0;
	while(v.size()!=0 and i<v.size()){
		if(aux_valor==v[i]){
			++cont;
			v.erase(v.begin()+i);
		}
		else
			++i;
	}
	return cont;
}
void omple_freq(vector<nat> &v, vector<nat> &freq) throw(error) {
//Omple el vector freq amb les frequencies
	while(v.size()!=0){
		nat aux_freq=get_cont(v);
		freq.push_back(aux_freq);
	}
}

arbbin<pair<nat,nat> > crear_arbre(nat index, nat freq){
//Crea arbre amb l'index i frequencia corresponent
	pair<nat,nat> node_info;
	node_info.first=index;
	node_info.second=freq;
	arbbin<pair<nat,nat> > aux_fills;
	arbbin<pair<nat,nat> > return_pare (node_info,aux_fills,aux_fills);
	return return_pare;
}
void moure_posicio(vector<arbbin<pair<nat,nat> > >&vec, nat i, const arbbin<pair<nat,nat> >& q){
//Mou l'arbre q a la posicio i del vector
	vec.push_back(q);
	nat cont=vec.size()-i-1;
	nat pos=vec.size()-1;
	while(cont!=0){
		swap(vec[pos],vec[pos-1]);
		--cont;
		--pos;
	}
}
void afegir(vector<arbbin<pair<nat,nat> > >& arbre_vector, const arbbin<pair<nat,nat> >& arbre){
//Afegeix l'arbre ordenat en el vector arbre_vector
	if(arbre_vector.size()==0)	arbre_vector.push_back(arbre);
	else{	
		bool afegit=false;
		arbbin<pair<nat,nat> >::iterador it;
		arbbin<pair<nat,nat> >::iterador it2=arbre.arrel();
		nat i=0;
		while(not afegit and i<arbre_vector.size()){	
			it=arbre_vector[i].arrel();	
			if((*it2).second==(*it).second and (*it).first>(*it2).first){
				moure_posicio(arbre_vector,i,arbre);
				afegit=true;
			}
			else if((*it2).second<(*it).second){
		  	moure_posicio(arbre_vector,i,arbre);
				afegit=true;
			}
			else{
				++i;
			}
		}
		if(not afegit)	arbre_vector.push_back(arbre);
		
	}
}

void r_codificacio(arbbin<pair<nat,nat> >::iterador it,vector<string>& p,string x){
//Omple el string x depenent del camí agafat, 0 esquerre 1 dreta
		string aux=x;
		if(it.fill_dret() and it.fill_esq()){
			if(it.fill_dret())	r_codificacio(it.fill_dret(),p,aux+'1');
			if(it.fill_esq()) r_codificacio(it.fill_esq(),p,aux+'0');
		}
		else	p[(*it).first]=aux;
}

void huffman::codi_huffman(const vector<nat>& seq, vector<string>& taula_codis) throw(error){

	if(seq.size()<2)
		throw error(SeqCurta);
	else{
		vector<nat> q= seq;		
		vector<nat> freq;
		omple_freq(q,freq);	
		vector<arbbin<pair<nat,nat> > > arbre_vector;
		for(nat i=0;i<freq.size();++i){
			arbbin<pair<nat,nat> > aux_afegir = crear_arbre(i,freq[i]);
			afegir(arbre_vector,aux_afegir);		
		}	
		if(freq.size() > 1){
			while(arbre_vector.size()>1){
				pair<nat,nat> aux_pair;
				arbbin<pair<nat,nat> >::iterador it=arbre_vector[0].arrel();
				arbbin<pair<nat,nat> >::iterador it2=arbre_vector[1].arrel();	
				if((*it).first>(*it2).first)	aux_pair.first=(*it2).first;
				else	aux_pair.first=(*it).first;
				aux_pair.second= (*it2).second + (*it).second;
				arbbin<pair<nat,nat> > arb(aux_pair,arbre_vector[0],arbre_vector[1]);
				arbre_vector.erase(arbre_vector.begin());
				arbre_vector.erase(arbre_vector.begin());
				afegir(arbre_vector,arb);
			}
			vector<string>aux_taula(freq.size());
			string x;
			r_codificacio(arbre_vector[0].arrel(),aux_taula, x);
			taula_codis=aux_taula;
		}
		else{
			string p="";
			taula_codis.push_back(p);
		}
	}
}
