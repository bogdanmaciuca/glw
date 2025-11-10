#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <utility>
#include "types.hpp"

namespace glw {
    template<typename...>
    class Vertex;

    template<>
    class Vertex<> {};

    template<typename H, typename... T>
    class Vertex<H, T...> {
    public:
        constexpr static usize field_num = 1 + sizeof...(T);

        Vertex() = default;

        template<typename Head, typename... Tail>
        explicit Vertex(Head&& h, Tail&&... t)
            : m_head(std::forward<Head>(h)), m_tail(std::forward<Tail>(t)...) {}

        template<unsigned int I>
        auto& get() {
            static_assert(I >= 0 && I < field_num, "Out of bounds");
            if constexpr (I == 0) return m_head;
            else return m_tail.template get<I-1>();
        }

        template<unsigned int I>
        const auto& get() const {
            static_assert(I >= 0 && I < field_num, "Out of bounds");
            if constexpr (I == 0) return m_head;
            else return m_tail.template get<I-1>();
        }
    private:
        H            m_head;
        Vertex<T...> m_tail;
    };

    template<typename... Types>
    auto MakeVertex(Types&&... args) {
        return Vertex<std::decay_t<Types>...>(std::forward<Types>(args)...);
    }

    template<typename T>
    struct IsVertexTrait : std::false_type {};
    template<typename... Types>
    struct IsVertexTrait<Vertex<Types...>> : std::true_type {};

    template<typename T>
    concept IsVertex = IsVertexTrait<T>::value;

    template<IsVertex V, typename F, usize I = 0, usize Offset = 0>
    void ForEachVertexField(const V& vertex, const F& func) {
        if constexpr (I < V::field_num) {
            func(I, vertex.template get<I>(), Offset);

            ForEachVertexField<V, F, I+1, Offset + sizeof(vertex.template get<I>())>(vertex, func);
        }
    }

}

#endif // VERTEX_HPP

