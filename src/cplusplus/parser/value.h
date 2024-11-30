#ifndef __GDB__VALUE__PARSER__H__
#define __GDB__VALUE__PARSER__H__

#include <string>
#include <vector>

namespace gdb {
    using namespace std;

    enum Type {
        RESULT,
        CONST,
        TUPLE,
        LIST,
        EMPTY
    };

    class Value {
        private:
            Type type;
        
        public:
            Value(Type t) : type(t) {};
            Value() : type(EMPTY) {};

            bool isResult() { return type == RESULT; };
            bool isConst()  { return type == CONST; };
            bool isTuple()  { return type == TUPLE; };
            bool isList()   { return type == LIST; };
            bool isEmpty()  { return type == EMPTY; };
    };


    class Result : public Value {
        private:
            pair<string, Value> result;
        
        public:
            Result(string variable, Value value) 
            : Value(RESULT)
            , result(make_pair(variable, value)) 
            {};
            Result()
            : Value(EMPTY)
            , result( make_pair("", Value()) )
            {};

    };

    class Const : public Value {
        private:
            string constant;
        
        public:
            Const(string constant)
            : Value(CONST)
            , constant(constant) 
            {};
    };

    class Tuple : public Value {
        private:
            vector<Value> values;

        public:
            Tuple(vector<Value> values)
            : Value(TUPLE)
            , values(values) 
            {};
            Tuple()
            : Value(TUPLE)
            , values() 
            {};
    };

    class List : public Value {
        private:
            vector<Value> values;

        public:
            List(vector<Value> values)
            : Value(LIST)
            , values(values)
            {};
            List()
            : Value(LIST)
            , values() 
            {};
    };

}



#endif