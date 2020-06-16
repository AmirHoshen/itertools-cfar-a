//
// Created by miros on 12/06/2020.
//


#ifndef CPPEX5_ITERTOOLS_COMPRESS_HPP
#define CPPEX5_ITERTOOLS_COMPRESS_HPP

#include <iostream>
#include <vector>

namespace itertools{
    template<typename CONTAINER1, typename CONTAINER2>
    class compress {
        CONTAINER1 _container;
        CONTAINER2 _boolContainer;
        typedef typename CONTAINER1::value_type value_type;

    public:
        compress(CONTAINER1 container, CONTAINER2 boolContainer): _container(container), _boolContainer(boolContainer){}

        class iterator{
            typename CONTAINER1::iterator _iter;
            typename CONTAINER1::iterator _end;
            typename CONTAINER2::iterator _boolIter;
        public:
            explicit iterator(typename CONTAINER1::iterator iter, typename CONTAINER1::iterator end, typename CONTAINER2::iterator boolIter)
                    : _iter(iter), _end(end), _boolIter(boolIter){
                while (_iter != _end && !(*_boolIter)){
                    ++_iter;
                    ++_boolIter;
                }
            }
            iterator(const iterator& other) = default;

            iterator& operator=(const iterator& other){
                if(this != &other){
                    this->_iter = other._iter;
                }
                return *this;
            };
            iterator& operator ++(){
                do{
                    ++_iter;
                    ++_boolIter;
                } while (_iter != _end && !(*_boolIter));
                return *this;
            }
            iterator operator ++(int){
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }
            bool operator ==(const iterator& other) {
                return (_iter == other._iter);
            }
            bool operator !=(const iterator& other) {
                return (_iter != other._iter);
            }
            value_type operator *(){
                return *_iter;
            }

        };
        iterator begin(){
            return iterator(_container.begin(), _container.end(), _boolContainer.begin());
        }
        iterator end(){
            return iterator(_container.end(), _container.end(), _boolContainer.end());
        }
    };
}


#endif //CPPEX5_ITERTOOLS_COMPRESS_HPP