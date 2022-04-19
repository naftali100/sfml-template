#pragma once
#ifndef CHAT_H
#define CHAT_H

#include <SFML/Network.hpp>
#include <iostream>

#include "State.h"

class ChatState : public State {
public:
    virtual void handleEvent(const sf::Event&) {};
    virtual void update(const sf::Time&) {};
    virtual void draw(sf::RenderTarget&) const {};

    ChatState(StateManager& sm) : State(sm) {
        sf::Thread* thread = nullptr;

        char who;
        std::cout << "Do you want to be a server (s) or a client (c) ? ";
        std::cin >> who;

        if (who == 's')
            Server();
        else if (who == 'c')
            Client();
        else {
            std::cout << "Unknown option";
            return;
        }

        thread = new sf::Thread(&ChatState::DoStuff, this);
        thread->launch();

        while (!quit) { GetInput(); }

        if (thread) {
            thread->wait();
            delete thread;
        }
    }

    void DoStuff(void) {
        static std::string oldMsg;
        while (!quit) {
            sf::Packet packetSend;

            {
                sf::Lock lock(globalMutex);
                packetSend << msgSend;
            }

            socket.send(packetSend);

            std::string msg;
            sf::Packet packetReceive;

            socket.receive(packetReceive);
            if ((packetReceive >> msg) && oldMsg != msg && !msg.empty()) {
                std::cout << msg << std::endl;
                oldMsg = msg;
            }
        }
    }

    void Server(void) {
        sf::TcpListener listener;
        listener.listen(PORT);
        listener.accept(socket);
        std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
    }

    bool Client(void) {
        if (socket.connect(IPADDRESS, PORT) == sf::Socket::Done) {
            std::cout << "Connected\n";
            return true;
        }
        return false;
    }

    void GetInput(void) {
        std::string s;
        std::cout << "\nEnter \"exit\" to quit or message to send: ";
        getline(std::cin, s);
        if (s == "exit")
            quit = true;

        {
            sf::Lock lock(globalMutex);
            msgSend = s;
        }
    }

private:
    const unsigned short PORT = 5000;
    const std::string IPADDRESS = "0.0.0.0";

    std::string msgSend;

    sf::TcpSocket socket;
    sf::Mutex globalMutex;
    bool quit = false;
};
#endif