Account = {}
Account.__index = Account
function Account:create(balance)
   local acnt = {}             -- our new object
   setmetatable(acnt,Account)  -- make Account handle lookup
   acnt.balance = balance      -- initialize our object
   return acnt
end

function Account:withdraw(amount)
   self.balance = self.balance - amount
end

--[[
Account.__tostringx = function (p)
    Account.__tostring = nil
    local s = "Account " .. tostring(p) .. " " .. p.balance
    Account.__tostring = Account.__tostringx
    return s
end

Account.__tostring = Account.__tostringx
]]

Point = {}
Point.__index = Point

function Point:create(x, y)
 local p = {}
 setmetatable(p, Point)
 p.x = x
 p.y = y
 return p
end

function Point:getx()
 return tonumber(self.x)
end

function Point:gety()
 return tonumber(self.y)
end

function Point:sety(y)
 self.y=y
end

function Point:setx(x)
 self.x=x
end

--[[
Point.__tostringx = function (p)
    Point.__tostring = nil
    local s = "Point " .. tostring(p) .. " " .. p.x .. "," .. p.y
    Point.__tostring = Point.__tostringx
    return s
end

Point.__tostring = Point.__tostringx
]]

-- create and use an Account
acc = Account:create(1000)
acc:withdraw(100)
print("account:", acc)


p1 = Point:create(0,0)
p2 = Point:create(3,0)
p3 = Point:create(3,4)

function dist(p1, p2) 
   local x1 = p1:getx()
   local x2 = p2:getx()
   local y1 = p1:gety()
   local y2 = p2:gety()
   local dx = x1 - x2
   local dy = y1 - y2
   return math.sqrt(dx*dx + dy*dy)
end
print(p1)
print(p2)
print(p3)
print(dist(p1,p3))
