#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <time.h>

using namespace std;

template<class G>
class cnode{
public:
    typedef typename G::N N;
    typedef typename G::edge edge;
    vector<edge *> m_edges;
    N x ,y;
    cnode(N _x, N _y){
    	this->x=_x;
    	this->y=_y;
    }
    void burbuja();
    ~cnode();
};

template<class G>
void cnode<G>::burbuja(){
	if(m_edges.size()>0){
		for (int i = 0; i < m_edges.size()-1; ++i)
		{
			for (int j = 0; j < m_edges.size()-1; ++j)
			{
				if(m_edges[j]->m_dato>m_edges[j+1]->m_dato){
					edge* temp;
					temp=m_edges[j];
					m_edges[j]=m_edges[j+1];
					m_edges[j+1]=temp;
				}

			}
		}
	}
}

template<class G>
class cedge{
public:
    typedef typename G::E E;
    typedef typename G::node node;
    node* m_nodes[2];
    E m_dato;
    bool m_dir;
    cedge(E e, node* a, node* b, bool d){
    	this->m_dato=e;
    	this->m_nodes[0]=a;
		this->m_nodes[1]=b;
		this->m_dir=d;
    }
    ~cedge();
};



template<class _N, class _E>
class cgrafo {
public:
    typedef cgrafo<_N,_E> self;
    typedef _N N;
    typedef _E E;
    typedef cnode<self> node;
    typedef cedge<self> edge;
    vector<node *> m_nodes;

    cHashTable<_N,fx<_N>,lista<_N>,97> b_hash;
    bool insert_nodo(_N _x, _N y);
    void create_matriz();
    bool insert_edge(E e, node* a, node* b, bool d);
    bool dijkstra(node* a, node* b);
    void print(node* temp);
    void construir(_E** mat);
    cgrafo(){};
    ~cgrafo(){  };
};

template<class _N, class _E>
bool cgrafo<_N,_E>::insert_nodo(_N x, _N y){
	_N n=x+y;
	if(b_hash.Find(n)) return false;
	node *temp;
	temp=new node(x,y); 
	m_nodes.push_back(temp);
	//b_hash.insert(n);
	return true;
}

template<class _N, class _E>
bool cgrafo<_N,_E>::insert_edge(E e, node* a, node* b, bool d){
	edge *temp;
	temp=new edge(e,a,b,d);
	if(d==1){
		a->m_edges.push_back(temp);
	}
	if(d==0){
		a->m_edges.push_back(temp);
		b->m_edges.push_back(temp);
	}
	return true;
}


template <class _N, class _E>
void cgrafo<_N,_E>::print(node* temp){
	if(temp==NULL)return;
	for(int i=0; i<temp->m_edges.size(); i++){
		if(temp->m_edges[i]->m_dir==1 && temp->m_edges[i]->m_nodes[0]->x==temp->x){
			cout<<temp->x<<","<<temp->y<<" -- "<<temp->m_edges[i]->m_dato<<" --> "<<temp->m_edges[i]->m_nodes[1]->x<<","<<temp->m_edges[i]->m_nodes[1]->y<<endl;
		}
	}
	for(int i=0; i<temp->m_edges.size(); i++){
		if(temp->m_edges[i]->m_dir==1 && temp->m_edges[i]->m_nodes[0]->x==temp->x){
			this->print(temp->m_edges[i]->m_nodes[1]);
		}
	}
	return;
}


int main(int argc, char const *argv[]){
    cout << "grafo" << endl;
	cgrafo<long,int> angel;

	angel.insert_nodo(10,10);
	angel.insert_nodo(30,10);
	angel.insert_nodo(10,30);
	angel.insert_nodo(30,30);

	angel.insert_edge(2,angel.m_nodes[0],angel.m_nodes[1],1);
	angel.insert_edge(10,angel.m_nodes[1],angel.m_nodes[2],1);
	angel.insert_edge(5,angel.m_nodes[2],angel.m_nodes[3],1);
	angel.insert_edge(1,angel.m_nodes[0],angel.m_nodes[2],1);
	angel.insert_edge(5,angel.m_nodes[0],angel.m_nodes[3],1);
	angel.insert_edge(1,angel.m_nodes[1],angel.m_nodes[3],1);

	angel.print(angel.m_nodes[0]);
}
