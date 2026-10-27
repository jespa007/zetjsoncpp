#pragma once

#define ZJ_BOOLEAN(name)                 	  (BOOLEAN, name)
#define ZJ_NUMBER(name)                 	  (NUMBER, name)
#define ZJ_STRING(name)                 	  (STRING, name)
#define ZJ_OBJECT(type, name) \
    (OBJECT, type, name)



#define ZJ_ARRAY_STRING(name)                 (ARRAY_STRING, name)
#define ZJ_ARRAY_NUMBER(name)                 (ARRAY_NUMBER, name)
#define ZJ_ARRAY_BOOLEAN(name)                (ARRAY_BOOLEAN, name)
#define ZJ_ARRAY_OBJECT(type, name)           (ARRAY_OBJECT, type, name)
#define ZJ_MAP_STRING(name)                   (MAP_STRING, name)
#define ZJ_MAP_NUMBER(name)                   (MAP_NUMBER, name)
#define ZJ_MAP_BOOLEAN(name)                  (MAP_BOOLEAN, name)
#define ZJ_MAP_OBJECT(type, name)             (MAP_OBJECT, type, name)
#define ZJ_MAP_ARRAY_STRING(name)             (MAP_ARRAY_STRING, name)
#define ZJ_ARRAY_STRING_NAMED(name, json_key) (ARRAY_STRING_NAMED, name, json_key)


#define ZJ_DECL_STRING(name)     		zetjsoncpp::StringJsonVar name{#name};
#define ZJ_DECL_NUMBER(name)     		zetjsoncpp::NumberJsonVar name{#name};
#define ZJ_DECL_BOOLEAN(name)    		zetjsoncpp::BooleanJsonVar name{#name};
#define ZJ_DECL_OBJECT(type, name) \
    zetjsoncpp::ObjectJsonVar<type> name{#name};

#define ZJ_DECL_ARRAY_STRING(name)     zetjsoncpp::ArrayStringJsonVar name{#name};
#define ZJ_DECL_ARRAY_NUMBER(name)     zetjsoncpp::ArrayNumberJsonVar name{#name};
#define ZJ_DECL_ARRAY_BOOLEAN(name)    zetjsoncpp::ArrayBooleanJsonVar name{#name};
#define ZJ_DECL_ARRAY_OBJECT(type, name)    zetjsoncpp::ArrayObjectJsonVar<type> name{#name};
#define ZJ_DECL_MAP_STRING(name)    zetjsoncpp::MapStringJsonVar name{#name};
#define ZJ_DECL_MAP_NUMBER(name)    zetjsoncpp::MapNumberJsonVar name{#name};
#define ZJ_DECL_MAP_BOOLEAN(name)  zetjsoncpp::MapBooleanJsonVar name{#name};
#define ZJ_DECL_MAP_OBJECT(type, name)  zetjsoncpp::MapObjectJsonVar<type> name{#name};
#define ZJ_DECL_MAP_ARRAY_STRING(name)  zetjsoncpp::MapArrayStringJsonVar name{#name};
#define ZJ_DECL_ARRAY_STRING_NAMED(name, json_key)  zetjsoncpp::ArrayStringJsonVar name{json_key};
#define ZJ_DECL_FIELD_I(kind, ...)    ZJ_DECL_##kind(__VA_ARGS__)
#define ZJ_DECL_FIELD(field)    ZJ_DECL_FIELD_I field

#define ZJ_VISIT_STRING(name)            _visitor(this->name);
#define ZJ_VISIT_NUMBER(name)            _visitor(this->name);
#define ZJ_VISIT_BOOLEAN(name)           _visitor(this->name);
#define ZJ_VISIT_OBJECT(type, name) \
    _visitor(this->name);

#define ZJ_VISIT_ARRAY_STRING(name)            _visitor(this->name);
#define ZJ_VISIT_ARRAY_NUMBER(name)            _visitor(this->name);
#define ZJ_VISIT_ARRAY_BOOLEAN(name)           _visitor(this->name);
#define ZJ_VISIT_ARRAY_OBJECT(type, name)      _visitor(this->name);
#define ZJ_VISIT_MAP_STRING(name)              _visitor(this->name);
#define ZJ_VISIT_MAP_NUMBER(name)              _visitor(this->name);
#define ZJ_VISIT_MAP_BOOLEAN(name)             _visitor(this->name);
#define ZJ_VISIT_MAP_OBJECT(type, name)        _visitor(this->name);
#define ZJ_VISIT_MAP_ARRAY_STRING(name)        _visitor(this->name);
#define ZJ_VISIT_ARRAY_STRING_NAMED(name, key) _visitor(this->name);
#define ZJ_VISIT_FIELD_I(kind, ...)    ZJ_VISIT_##kind(__VA_ARGS__)
#define ZJ_VISIT_FIELD(field)     ZJ_VISIT_FIELD_I field


#define ZJ_FE_1(M,a) M(a)
#define ZJ_FE_2(M,a,...) M(a) ZJ_FE_1(M,__VA_ARGS__)
#define ZJ_FE_3(M,a,...) M(a) ZJ_FE_2(M,__VA_ARGS__)
#define ZJ_FE_4(M,a,...) M(a) ZJ_FE_3(M,__VA_ARGS__)
#define ZJ_FE_5(M,a,...) M(a) ZJ_FE_4(M,__VA_ARGS__)
#define ZJ_FE_6(M,a,...) M(a) ZJ_FE_5(M,__VA_ARGS__)
#define ZJ_FE_7(M,a,...) M(a) ZJ_FE_6(M,__VA_ARGS__)
#define ZJ_FE_8(M,a,...) M(a) ZJ_FE_7(M,__VA_ARGS__)

#define ZJ_NARG_I(_1,_2,_3,_4,_5,_6,_7,_8,N,...) N

#define ZJ_NARG(...) \
    ZJ_NARG_I(__VA_ARGS__,8,7,6,5,4,3,2,1)

#define ZJ_JOIN_I(a,b) a##b
#define ZJ_JOIN(a,b) ZJ_JOIN_I(a,b)

#define ZJ_FOR_EACH(M,...) \
    ZJ_JOIN(ZJ_FE_,ZJ_NARG(__VA_ARGS__))(M,__VA_ARGS__)

#define ZJ_DEFINE_OBJECT(type, ...) \
    struct type { \
        ZJ_FOR_EACH(ZJ_DECL_FIELD,__VA_ARGS__) \
        template<typename _F> \
        void visitFields(_F &&_visitor) { \
            ZJ_FOR_EACH(ZJ_VISIT_FIELD,__VA_ARGS__) \
        } \
        template<typename _F> \
        void visitFields(_F &&_visitor) const { \
            ZJ_FOR_EACH(ZJ_VISIT_FIELD,__VA_ARGS__) \
        } \
    }
