#ifndef PREP_RING_BUFF_CPP
#define PREP_RING_BUFF_CPP
#include <algorithm>
#include <array>
#include <cstddef>
#include <mutex>
#include <memory>
#include <optional>
namespace prep{
    
    template <typename T,size_t BUF_SIZE>
    class Ringbuf{
        public:
        Ringbuf(){;}
        [[nodiscard]]bool push(std::unique_ptr<T>&& ptr){
            const std::lock_guard<std::mutex> lock(readWriteMutex);
            if(full_){
                return false;
            }
            internalBuf.at(pushCursor_)=std::move(ptr);
            pushCursor_=(pushCursor_+1)%BUF_SIZE;
            full_=(pushCursor_==popCursor_);
            return true;
        }
        [[nodiscard]]std::optional<std::unique_ptr<T>> pop(){
            const std::lock_guard<std::mutex> lock(readWriteMutex);
            if(isEmpty()){
                return std::nullopt;
            }
            auto ret = std::move(internalBuf.at(popCursor_));
            internalBuf.at(popCursor_).reset();
            popCursor_=(popCursor_+1)%BUF_SIZE;
            full_=false;
            return ret;
        }
        [[nodiscard]] bool inline isEmpty()  noexcept{
            const std::lock_guard<std::mutex> lock(fullMutex);
            auto retval = (!full_) && (pushCursor_==popCursor_);
            return retval;
        }
        [[nodiscard]] bool inline isFull()  noexcept{
            const std::lock_guard<std::mutex> lock(fullMutex);
            auto retval = full_;
            return retval;
        }
        [[nodiscard]] size_t capacity() const noexcept{
            return BUF_SIZE;
        }
        const std::unique_ptr<T> operator [](const int idx) const {
            return internalBuf.at(idx);
        }
    private:
        static_assert((BUF_SIZE-1)<SIZE_MAX);
        std::array<std::unique_ptr<T>,BUF_SIZE> internalBuf;
        std::mutex readWriteMutex;
        std::mutex fullMutex;
        size_t pushCursor_{0};
        size_t popCursor_{0};
        bool full_{false};
    };
}
#endif