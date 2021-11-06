#pragma once
#include <emscripten/fetch.h>
#include <unordered_map>
namespace reactdom {

template<class T>
struct FetchPromise {
    friend struct Fetch;
    using This = FetchPromise<T>;
    using FetchId = decltype(emscripten_fetch_t::id);
    FetchPromise(emscripten_fetch_attr_t* attr, const char* url)
    : fetch_id_(0)
    {
        attr->onerror = on_error;
        attr->onsuccess = on_success;
        auto tmp = emscripten_fetch(attr, url);
        fetch_id_map()[tmp->id] = nullptr;
        fetch_id_ = tmp->id;
    }
    T await() {
        auto*& p_fetch = fetch_id_map().at(fetch_id_);
        while(p_fetch == nullptr) {
            emscripten_sleep(1);
        }
        if(p_fetch->status != 200) {
            throw std::runtime_error("fetch data failed");
        }
        if constexpr(!std::is_same_v<T, std::string>) {
            throw std::runtime_error("FetchPromise currently only support string");
        }
        std::string res(p_fetch->data, p_fetch->totalBytes);
        emscripten_fetch_close(p_fetch);
        fetch_id_map().erase(fetch_id_);
        return res;
    }
private:
    using FetchResIdMap = std::unordered_map<FetchId, emscripten_fetch_t*>;
    static FetchResIdMap& fetch_id_map() {
        static FetchResIdMap g_map;
        return g_map;
    };
    static void on_success(emscripten_fetch_t* res) {
        fetch_id_map().at(res->id) = res;
    }
    static void on_error(emscripten_fetch_t* res) {
        fetch_id_map().at(res->id) = res;
    }
    FetchId fetch_id_;
};

struct Fetch {
    Fetch() {
        emscripten_fetch_attr_init(&attr_);
        attr_.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    }
    template<class T>
    auto get(const std::string& url) {
        std::strcpy(attr_.requestMethod, "GET");
        FetchPromise<T> res(&attr_, url.c_str());
        return res;
    }

private:
   emscripten_fetch_attr_t attr_; 
};

} // namespace reactdom
