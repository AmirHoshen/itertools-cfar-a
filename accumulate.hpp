//
// Created by miros on 12/06/2020.
//

#ifndef CPPEX5_ITERTOOLS_ACCUMULATE_HPP
#define CPPEX5_ITERTOOLS_ACCUMULATE_HPP
namespace itertools{
    typedef struct{
        template <typename T>
        T operator ()(T a, T b) const{
            return a+b;
        }
    } plus;

    template <typename CONTAINER, typename  FUNCTION = plus>
    class accumulate{
        CONTAINER _container;
        FUNCTION _function;
        typedef typename CONTAINER::value_type value_type;
    public:
        explicit accumulate(CONTAINER container, FUNCTION function = plus())
                : _container(container), _function(function){}

        class iterator{
            decltype(*(_container.begin())) _data;
            typename CONTAINER::iterator _iter;
            typename CONTAINER::iterator _end;
            FUNCTION _function;
        public:
            explicit iterator(typename CONTAINER::iterator iter, typename CONTAINER::iterator end, FUNCTION function)
                    : _iter(iter), _end(end), _function(function), _data(*iter){};
            iterator(const iterator& other) = default;
            iterator& operator=(const iterator& other){
                if(this != &other) {
                    this->_data = other._data;
                    this->_iter = other._iter;
                    this->_end = other._end;
                    this->_function = other._function;
                }
                return *this;
            };
            iterator& operator ++(){
                ++_iter;
                if(_iter != _end)
                    _data = _function(_data, *_iter);
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

            auto operator *(){
                return _data;
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

#endif //CPPEX5_ITERTOOLS_ACCUMULATE_HPP