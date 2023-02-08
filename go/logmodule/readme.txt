  reference: https://zerokspot.com/weblog/2021/10/30/go-logr/

  mkdirg logmodule
  cd logmodule/
  go mod init logmodule
  cat go.mod
  go get github.com/go-logr/logr
  go get github.com/go-logr/zerologr
  go get github.com/rs/zerolog
  cat go.mod
  go run ex1.go
