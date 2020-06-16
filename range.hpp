//
// Created by miros on 12/06/2020.
//

#ifndef CPPEX5_ITERTOOLS_RANGE_HPP
#define CPPEX5_ITERTOOLS_RANGE_HPP
namespace itertools{
    class range{
        int _begin, _end;

    public:
        range(int begin, int end): _begin(begin), _end(end){}

        class iterator{
            int _data;
        public:
            explicit iterator(int data): _data(data) {};
            iterator(const iterator& other) = default;
            iterator& operator=(const iterator& other){
                if(this != &other)
                    this->_data = other._data;
                return *this;
            };
            iterator& operator ++(){
                ++_data;
                return *this;
            }
            iterator operator ++(int){
                iterator tmpIter = *this;
                ++_data;
                return tmpIter;
            }
            bool operator ==(const iterator& other) {
                return (_data == other._data);
            }
            bool operator !=(const iterator& other) {
                return (_data != other._data);
            }
            int operator *(){
                return _data;
            }
        };

        iterator begin(){
            return iterator(_begin);
        }
        iterator end(){
            return iterator(_end);
        }


        typedef int	value_type;
    };
}
#endif //CPPEX5_ITERTOOLS_RANGE_HPP