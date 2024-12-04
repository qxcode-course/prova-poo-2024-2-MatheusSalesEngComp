#include <iostream>
#include "fn.hpp"


class Pessoa{
private: 
    std::string nome;
    int dinheiro;

public:
    Pessoa(): nome(""), dinheiro(0) {}

    std::string getNome () { return nome; }

    int getDinheiro () const { return dinheiro; }

    void setNome(const std::string &novoNome) { nome = novoNome; }
    void setDinheiro(int novoDinheiro) { dinheiro = novoDinheiro; }


};

class Moto{
private: 
    int custo;
    std::shared_ptr<Pessoa> motorista;
    std::shared_ptr<Pessoa> passageiro;

public:
    Moto(): custo(0), motorista(nullptr), passageiro(nullptr) {}

    int getCusto () const { return custo; }
    std::shared_ptr<Pessoa> getMotorista () { return motorista; }
    std::shared_ptr<Pessoa> getPassageiro () { return passageiro; }

    void setCusto (int novoCusto) { custo = novoCusto; }
    void setMotorista(std::shared_ptr<Pessoa> novoMotorista) { motorista = novoMotorista; }
    void setPassageiro(std::shared_ptr<Pessoa> novoPassageiro) { passageiro = novoPassageiro; }

};

class Adapter {
private:
    std::shared_ptr<Moto> moto;
    std::shared_ptr<Pessoa> pessoa;

public:

    void setPessoa (std::shared_ptr<Pessoa> person) {
        this->pessoa = person;
    }

    void setMoto (std::shared_ptr<Moto> mot) {
        this->moto = mot;
    }


    void setDriver(std::string name, int money) {
        auto driver = std::make_shared<Pessoa>();
        driver->setNome(name);
        driver->setDinheiro(money);
        moto->setMotorista(driver);
    }
    
    void setPass(std::string name, int money) {
        if (!moto->getMotorista()){
            fn::write("Não há motorista.");
            return;
        }
        auto pass = std::make_shared<Pessoa>();
        pass->setNome(name);
        pass->setDinheiro(money);
        moto->setPassageiro(pass);
    }

    void drive(int distance) {
        if ((!moto->getMotorista()) || (!moto->getPassageiro())){
            fn::write("Não há motorista ou passageiro.");
            return;
        }
        moto->setCusto(distance);
    }
    
    void leavePass() {
        
    }
    void show() {
        fn::write("Motorista: " + (moto->getMotorista() ? moto->getMotorista()->getNome() : "none") + 
              ", Passageiro: " + (moto->getPassageiro() ? moto->getPassageiro()->getNome() : "none") + 
              ", Custo: " + std::to_string(moto->getCusto()) + "\n");

    }
};

int main() {
    Adapter adp;
    while (true) {
        fn::write("$", "");
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write(line);

        if      (args[0] == "end")       { break;                                  }
        else if (args[0] == "setDriver") { adp.setDriver(args[1], +args[2]);       }
        else if (args[0] == "setPass")   { adp.setPass(args[1], +args[2]);         }
        else if (args[0] == "drive")     { adp.drive(+args[1]);                    }
        else if (args[0] == "leavePass") { adp.leavePass();                        }
        else if (args[0] == "show")      { adp.show();                             }
        else                             { fn::write("fail: command not found\n"); }
    }
}
