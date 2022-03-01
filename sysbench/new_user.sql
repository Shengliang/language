create user 'test'@'localhost' identified by 'rivos';
grant all on *.* to 'test'@'localhost';
flush privileges;
