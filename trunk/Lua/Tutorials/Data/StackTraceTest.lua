function f3()
    error("An Error", 2)
end

function f2()
    f3()
end

function f1()
    f2()
end

f1()