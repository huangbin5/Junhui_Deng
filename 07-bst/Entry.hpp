template <typename K, typename V> struct Entry {
    K key;
    V value;

    Entry(K k = K(), V v = V())
        : key(k)
        , value(v){};
    Entry(const Entry<K, V>& e)
        : key(e.key)
        , value(e.value) {}

    bool operator<(const Entry<K, V>& e) { return key < e.key }
    bool operator>(const Entry<K, V>& e) { return key > e.key }
    bool operator==(const Entry<K, V>& e) { return key == e.key }
    bool operator!=(const Entry<K, V>& e) { return key != e.key }
};