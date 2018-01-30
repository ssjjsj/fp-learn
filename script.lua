function test()
    print("enter test")
    coroutine.yield()
    print("leave test")    
end

test()