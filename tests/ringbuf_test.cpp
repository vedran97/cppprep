#include <gtest/gtest.h>
#include <memory>
#include "ringbuffer.hpp"

TEST(Ringbuf, PUSH_TEST) {
  prep::Ringbuf<int, 100> ringBuf;
  bool ret = ringBuf.push(std::make_unique<int>(100));
  EXPECT_EQ(ret, true);
}

TEST(Ringbuf, POP_TEST) {
  prep::Ringbuf<int, 100> ringBuf;
  bool ret = ringBuf.push(std::make_unique<int>(100));
  EXPECT_EQ(ret, true);
  auto pop = ringBuf.pop();
  ASSERT_TRUE(pop.has_value());
  ASSERT_TRUE(*pop->get()==100);
}

TEST(Ringbuf, PUSH_POP_TEST) {
constexpr static size_t N=100;
prep::Ringbuf<size_t, N> ringBuf;
for(size_t i=0;i<N;i++){
  auto ret =ringBuf.push(std::make_unique<size_t>(i));
  EXPECT_EQ(ret, true);
}
for(size_t i=0;i<N;i++){
  auto pop = ringBuf.pop();
  ASSERT_TRUE(pop.has_value());
  ASSERT_TRUE(*pop->get()==i);  
}
}

TEST(Ringbuf, PUSH_POP_TEST_FAIL) {
constexpr static size_t N=100;
prep::Ringbuf<size_t, N> ringBuf;
for(size_t i=0;i<=N;i++){
  auto ret =ringBuf.push(std::make_unique<size_t>(i));
  if(i==N){
    EXPECT_EQ(ret, !true);
  }
  else{EXPECT_EQ(ret, true);}
}
for(size_t i=0;i<=N;i++){
  auto pop = ringBuf.pop();
  if(i==N){
    ASSERT_FALSE(pop.has_value()); 
  }else{
    ASSERT_TRUE(pop.has_value());
    ASSERT_TRUE(*pop->get()==i); 
  }
}
}