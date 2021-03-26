class Fibnacci {
private:
    //前一项，当前项
    int pre, cur;

public:
    //求出大于n的最小Fibonacci数
    Fibnacci(int n) {
        //初始时，cur为第0项=0，pre=1可方便计算第1项1
        pre = 1;
        cur = 0;
        while (cur < n)
            next();
    }

    //获取当前项
    int get() {
        return cur;
    }

    //计算下一项
    int next() {
        cur += pre;
        pre = cur - pre;
        return cur;
    }

    //计算前一项
    int prev() {
        pre = cur - pre;
        cur -= pre;
        return cur;
    }
};