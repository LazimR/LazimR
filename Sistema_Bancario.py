class Conta:
    def __init__(self,user,key):
        self.user = user
        self.key = key
        self.saldo = 0

    def saque(self,user,key,valor):
        if user == self.user and key == self.key:
            if (self.saldo - valor) > 0:
                self.saldo = self.saldo - valor
                print(f'Saque feito com sucesso\nSaldo:{self.saldo}\n')
            else:
                print('Saldo insuficiente\n')

    def depositar(self,user,valor):
        if user == self.user:
            self.saldo += valor
            print(f'Deposito feito com sucesso\nSaldo:{self.saldo}\n')
    def extrato(self):
        print('Saldo:',self.saldo,'\n')

def banco(conta):
    while True:
        opc = int(input('1 - Saque\n2 - Deposito\n3 - Extrato\n4 - Sair\n'))
        if opc == 1:
            user = input('Login:')
            key = int(input('Senha:'))
            valor = float(input('Quantidade:'))
            conta.saque(user,key,valor)
            mudaSaldo(conta)

        elif opc == 2:
            user = input('Login:')
            valor = float(input('Quantidade:'))
            conta.depositar(user,valor)
            mudaSaldo(conta)

        elif opc == 3:
            conta.extrato()

        elif opc == 4:
            break
        
        else:
            print('Opção invalida')

def mudaSaldo(conta):
    with open('banco.txt','r') as arquivo:
        linhas = arquivo.readlines()

    linhas[linhas.index(str(conta.user)+'\n')+2] = str(conta.saldo)+'\n'

    with open('banco.txt','w') as arquivo:
        arquivo.writelines(linhas)

    
while True:
    opc = input('1 - Login\n2 - Cadastrar\n3 - Sair\n')
    if opc == '1':
        arquivo = open('banco.txt','r')
        user = input('Login:')
        key = input('Senha:')
        while True:
            info = arquivo.readline()
            if info == user+'\n':
                info = arquivo.readline()
                if info == key+'\n':
                    c = Conta(user,int(key))
                    c.saldo = float(arquivo.readline())
                    arquivo.close()
                    banco(c)
                    break
            elif info == '':
                arquivo.close()
                break
        

    elif opc == '2':
        arquivo = open('banco.txt','a')
        user = input('Informe o login:')
        key =  input('Informe a senha:')
        arquivo.write(user+'\n')
        arquivo.write(key+'\n')
        arquivo.write('0\n')
        arquivo.close()
        
    elif opc == '3':
        break
    else:
        print('Opção invalida')

