//
// Created by miros on 12/06/2020.
//


#ifndef CPPEX5_ITERTOOLS_FILTERFALSE_HPP
#define CPPEX5_ITERTOOLS_FILTERFALSE_HPP

#include <iostream>
#include <vector>

namespace itertools{
    template<typename FUNCTION, typename CONTAINER>
    class filterfalse {
        FUNCTION _function;
        CONTAINER _container;
        typedef typename CONTAINER::value_type value_type;

    public:
        filterfalse(FUNCTION function, CONTAINER container): _function(function), _container(container){}

        class iterator{
            typename CONTAINER::iterator _iter;
            typename CONTAINER::iterator _end;
            FUNCTION _function;
        public:
            explicit iterator(typename CONTAINER::iterator iter, typename CONTAINER::iterator end, FUNCTION function)
                    : _iter(iter), _end(end), _function(function){

                while (_iter != _end && _function(*_iter))
                    ++_iter;
            }
            iterator(const iterator& other) = default;

            iterator& operator=(const iterator& other){
                if(this != &other) {
                    this->_iter = other._iter;
                    this->_end = other._end;
                    this->_function = other._function;
                }
                return *this;
            };
            iterator& operator ++(){
                do{
                    ++_iter;
                } while (_iter != _end && _function(*_iter));
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
            return iterator(_container.begin(), _container.end(), _function);
        }
        iterator end(){
            return iterator(_container.end(), _container.end(), _function);
        }
    };
}
#endif //CPPEX5_ITERTOOLS_FILTERFALSE_HPP