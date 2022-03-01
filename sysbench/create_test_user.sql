create user 'ssl'@'127.0.0.1' identified by 'rivos';
create user 'ssl'@'::1' identified by 'rivos';
grant all on *.* to 'ssl'@'127.0.0.1';
flush privileges;
