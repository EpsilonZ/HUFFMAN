template <typename Elem>
arbbin<Elem>::iterador:: iterador() throw(error) : _n(NULL) {}
template<typename Elem>
arbbin<Elem>::iterador::iterador(const arbbin<Elem>::iterador& it) throw(error){
	_n=it._n;
}
template <typename Elem>
typename arbbin<Elem>::iterador& arbbin<Elem>::iterador::operator=(const arbbin<Elem>::iterador& it) throw(error){
	_n=it._n;
	return *this;
}
template <typename Elem>
arbbin<Elem>::iterador:: ~iterador() throw(){}
template <typename Elem>
Elem arbbin<Elem>::iterador::operator*() const throw(error){
	if(_n==NULL)	throw error(IteradorNul);
	else	return _n->_info;	
}
template <typename Elem>
typename arbbin<Elem>::iterador arbbin<Elem>::iterador:: fill_esq() const throw(error){
	if(_n==NULL) throw error(IteradorNul);
	arbbin<Elem>::iterador it;
	it._n=_n->_fesq;
	return it;
}
template <typename Elem>
typename arbbin<Elem>::iterador arbbin<Elem>::iterador::fill_dret() const throw(error){
	if(_n==NULL) throw error(IteradorNul);
	arbbin<Elem>::iterador it;
	it._n=_n->_fdret;
	return it;
}
template <typename Elem>
 arbbin<Elem>::iterador:: operator bool() const throw(){
	return _n!=NULL;
}
template <typename Elem>
arbbin<Elem>::arbbin() throw(error) {
	_head=NULL;
	_num_elements=0;
}
template <typename Elem>
arbbin<Elem>::arbbin(const Elem& x, const arbbin& fesq, const arbbin& fdret) throw(error){
	node *aux=new node;
	try{
		aux->_info=x;
	}
	catch(...){
		delete aux;
		throw;
	}
	_head=aux;
	_head->_fesq=_copy(fesq._head);
	_head->_fdret=_copy(fdret._head);
	_num_elements=fesq._num_elements+fdret._num_elements+1;
}
template <typename Elem>
arbbin<Elem>::arbbin(const arbbin<Elem>& a) throw(error){
	_head=_copy(a._head);
	_num_elements=a._num_elements;
	
}
template <typename Elem>
typename arbbin<Elem>::node* arbbin<Elem>::_copy(node* cmp) throw(error){
	if(cmp==NULL) return NULL;
	else{
		node *aux_new= new node;
		try{
			aux_new->_info=cmp->_info;
		}
		catch(...){
			delete aux_new;
			throw;
		}
		node *fdret=NULL;
		node *fesq=NULL;
		if(cmp!=NULL)	fesq=_copy(cmp->_fesq);
		if(cmp!=NULL)	fdret=_copy(cmp->_fdret);
		aux_new->_fesq=fesq;
		aux_new->_fdret=fdret;
		return aux_new;
	}
}

template <typename Elem>
arbbin<Elem>& arbbin<Elem>::operator=(const arbbin& a) throw(error){
	if(_head!=a._head){
		aux_destructora(_head);
		_head=_copy(a._head);
		_num_elements=a._num_elements;
	}
	
	return *this;
}
template <typename Elem>
arbbin<Elem>:: ~arbbin() throw(){
	aux_destructora(_head);
	_num_elements=0;
}
template<typename Elem>
void arbbin<Elem>::aux_destructora(node *aux_del) throw(){
	if(aux_del!=NULL){
		aux_destructora(aux_del->_fesq);
		aux_destructora(aux_del->_fdret);
		delete aux_del;
	}
}
template <typename Elem>
util::nat arbbin<Elem>:: size() const throw(){
	return _num_elements;
}
template <typename Elem>
typename arbbin<Elem>::iterador arbbin<Elem>:: arrel() const throw(){
	arbbin<Elem>::iterador it;
	it._n= _head;
	return it;
}
