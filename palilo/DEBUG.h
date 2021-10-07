#ifdef palilo
template <typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream& operator<<(ostream& os, const C& container) {
    os << '[';
    bool first = true;
    for (const auto& x : container) {
        if (!first) os << ", ";
        os << x;
        first = false;
    }
    return os << ']';
}

template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

template <typename T>
void debug_msg(string name, T arg) {
    cerr << name << " = " << arg << endl;
}

template <typename T1, typename... T2>
void debug_msg(string names, T1 arg, T2... args) {
    cerr << names.substr(0, names.find(',')) << " = " << arg << " | ";
    debug_msg(names.substr(names.find(',') + 2), args...);
}

#define debug(...) cerr << '(' << __LINE__ << ')' << ' ', debug_msg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...)
#endif
