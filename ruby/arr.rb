
array = [1,3,4,71,11]
num = 5

def isSum(array, sum)
	array.each do |x|
	 array.each do |y|
	   return "yes:",x,y if sum == (x+y) and x!= y
	 end
	end
   return "no"
end

puts isSum(array, num)

