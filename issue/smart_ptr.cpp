template <typename T>
class shared_smart_ptr {
public:
 explicit shared_smart_ptr(T* ptr = nullptr){
  ptr_ = ptr;
  if (ptr_) {
   count_ = new int(1);
  }
 }
// 析构函数
 ~shared_smart_ptr() {
  // ptr_为nullptr，不需要做任何处理
  if (ptr_ == nullptr) {
   return;
  }

  // 计数器减一
  --(*count_);

  // 计数器减为0，回收对象
  if (*count_ == 0) {
   delete ptr_;
   delete count_;
  }
 }
// 移动构造函数
 shared_smart_ptr(shared_smart_ptr&& other) {
  ptr_ = other.ptr_;
  count_ = other.count_;
  
  other.ptr_ = nullptr;
  other.count_ = nullptr;
 }
// 拷贝构造函数
 shared_smart_ptr(const shared_smart_ptr& other) {
  ptr_ = other.ptr_;
  count_ = other.count_;
  if (ptr_) {
   (*count_)++;
  }
 }
// 赋值构造函数
 shared_smart_ptr& operator = (shared_smart_ptr rhs) {
  std::swap(rhs.ptr_, this->ptr_);
  std::swap(rhs.count_, this->count_);
  return *this;
 }

 int use_count() const { return *count_; };

 T& operator*() const { return *ptr_; };

 T* operator->() const { return ptr_; };

private:
 T* ptr_;
 int* count_;
};