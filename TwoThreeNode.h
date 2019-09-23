template <class T>
class TwoThreeNode{
public:
    bool hasSmall = false;
    bool hasHigh = false;
    bool full = false;
    T* small = nullptr;
    T* big = nullptr;
    T* tempMiddle = nullptr;
    TwoThreeNode<T>* parent = nullptr;
    TwoThreeNode<T>* left = nullptr;
    TwoThreeNode<T>* middle = nullptr;
    TwoThreeNode<T>* right = nullptr;
    TwoThreeNode<T>* temp = nullptr;
    TwoThreeNode<T>():left(nullptr),middle(nullptr),right(nullptr),parent(nullptr),small(nullptr),big(nullptr),tempMiddle(nullptr),temp(nullptr){}
    TwoThreeNode(T _small){
        small = new T(_small);
        hasSmall = true;
    }
    virtual ~TwoThreeNode(){
        left = middle = right = parent = temp = nullptr;
        small = big = nullptr;
    }

    TwoThreeNode<T>* getTemp(){
        return temp;
    }

    void setTemp(TwoThreeNode<T>* node){
        temp = node;
    }

    T getTempMiddle(){
        return *tempMiddle;
    }

    void deleteTempMiddle(){
      if(tempMiddle)
        tempMiddle = nullptr;
    }

    void setTempMiddle(T _info){
      if(tempMiddle == nullptr)
        tempMiddle = new T(_info);
      else
        *tempMiddle = _info;
    }

    bool hasTempMiddle(){
      if(tempMiddle)
          return true;
      else
          return false;
    }

    void setSmall(T _info){
      if(small!=nullptr)
        *small = _info;
      else
          small = new T(_info);
    }

    void setBig(T _info){
      if(big!=nullptr)
        *big = _info;
      else
        big = new T(_info);
    }

    T getSmall(){
      return *small;
    }

    T getBig(){
      return *big;
    }

    bool isFull() {
      if(big && small)
          return true;
      return false;
    }

    bool hasThreeKeys(){
      return big && small && tempMiddle;
    }

    void setInfo(T _info){
      if(!small){
          small = new T(_info);
      }
      else {
          if(_info >= *small) {
              if(!big)
                big = new T(_info);
          }
          else if(_info < *small) {
              big = new T(*small);
              *small = _info;
          }
      }
    }

    void deleteKeys() {
        if(small)
            small = nullptr;
        if(big)
            big = nullptr;
    }

    void setInfoMiddle(T _info){
      if(big && small){
        if(!tempMiddle){
          tempMiddle = new T(_info);
          if(_info < *small){
            *tempMiddle = *small;
            *small = _info;
          }
          else if(_info >= *small && _info <= *big){
            *tempMiddle = _info;
          }
          else {
            *tempMiddle = *big;
            *big = _info;
          }
        }
        else {
          if(_info < *small){
            *tempMiddle = *small;
            *small = _info;
          }
          else if(_info >= *small && _info <= *big){
            *tempMiddle = _info;
          }
          else{
            *tempMiddle = *big;
            *big = _info;
          }
        }
      }
    }

    void deleteBig(){
      if(big)
        big = nullptr;
    }

    void deleteSmall() {
      if(small)
          small = nullptr;
    }

    void changeBigToSmall() {
      if(!small)
          small = new T(*big);
      else
          *small = *big;
      big = nullptr;
    }


    bool hasLower(){
      if(small==nullptr)
        return false;
      else
        return true;
    }

    bool hasHigher(){
      if(big==nullptr)
        return false;
      else
        return true;
    }

    bool noKeys(){
        return !small && !big;
    }

    TwoThreeNode<T> * getLeft() const { return left; }
    void setLeft(TwoThreeNode<T> * info) { left = info; }

    TwoThreeNode<T> * getRight() const { return right; }
    void setRight(TwoThreeNode<T> * info) { right = info; }

    TwoThreeNode<T> * getMiddle() const { return middle; }
    void setMiddle(TwoThreeNode<T> * info) { middle = info; }

    TwoThreeNode<T> * getParent() const { return parent; }
    void setParent(TwoThreeNode<T> * info) { parent = info; }
};
