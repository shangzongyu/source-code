.pragma library

var factorialCount = 0;

function factorial(a) {
    a = parseInt(a);

    // 阶乘递归
    if (a > 0)
        return a * factorial(a - 1);

    // 共享状态
    factorialCount += 1;

    return 1;
}

function factorialCallCount() {
    return factorialCount;
}
