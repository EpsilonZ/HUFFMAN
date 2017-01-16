#ifndef _ARBBIN_HPP_
#define _ARBBIN_HPP_
#include <iostream>
#include <esin/error>
#include <esin/util>
using namespace std;

using util::nat;

template <typename Elem>
class arbbin {
private:
	struct node{
			Elem _info;
			node *_fdret;
			node *_fesq;
		};
	nat _num_elements;
	node *_head;

	void aux_destructora(node *aux_del) throw();
	node* _copy(node* cmp) throw(error);

public:

  friend class iterador;

  class iterador {

    friend class arbbin;

  public:

    iterador() throw(error);
         
    iterador(const iterador& it) throw(error);
    iterador& operator=(const iterador& it) throw(error);
    ~iterador() throw();
         
    Elem operator*() const throw(error);
         
    iterador fill_esq() const throw(error);
         
    iterador fill_dret() const throw(error);
         
    operator bool() const throw();
         
    static const int IteradorNul = 11;

  private:
			arbbin<Elem>::node *_n;
		
		};
	arbbin() throw(error);

	arbbin(const Elem& x, const arbbin& fesq, const arbbin& fdret) throw(error);
	arbbin(const arbbin& a) throw(error);


	arbbin& operator=(const arbbin& a) throw(error);

	~arbbin() throw();

	nat size() const throw();

	iterador arrel() const throw();
};
#include "arbbin.t"
#endif
