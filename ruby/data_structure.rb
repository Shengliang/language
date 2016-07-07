=begin
 * ref: 
 * http://tryruby.org/levels/1/challenges/0
 * http://robdayz.readthedocs.io/es/latest/ruby.html
 *
=end
print "123456789".reverse
print 40.to_s.reverse

arr = [1, 2, 3]
print arr
print arr.max
books = {}
=begin
 * Here's our rating system.
 * :splendid → a masterpiece.
 * :quite_good → enjoyed, sure, yes.
 * :mediocre → equal parts great and terrible.
 * :quite_not_good → notably bad.
 * :abysmal → steaming wreck.
=end
books['A'] =:splendid
books['B'] =:splendid
books['C'] =:quite_good
books['D'] =:mediocre
books['E'] =:mediocre
books['F'] =:mediocre
books['G'] =:quite_not_good
books['H'] =:abysmal

print books
ratings = Hash.new(0)
books.values.each { |rate| ratings[rate] += 7 }

3.times { print "A" }
print Dir["/*.txt"]
print File.read("comics.txt")
print File.mtime("comics.txt")
# FileUtils.cp('comics.txt', 'comics.copy.txt')
File.open("comics.copy.txt", "a") do |f|
  f << "Cat and Girl: http://catandgirl.com/"
end
print File.mtime("comics.copy.txt")
print File.mtime("comics.copy.txt").hour
def load_file(path)
  comics = {}
  File.foreach(path) do | line|
     name, url = line.split(': ')
     comics[name] = url.strip
  end
  comics
end
comics = load_file('comics.txt')
print comics
