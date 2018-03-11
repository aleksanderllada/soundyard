#pragma once

#ifndef BACKGROUNDS_H_INCLUDED
#define BACKGROUNDS_H_INCLUDED

namespace Backgrounds
{

    class InGameBackground
    {
    public:
        virtual void Init(){}
        virtual void Render(){}
        virtual void Update(){}
    };

    class InfernoBackground : public InGameBackground
    {
    public:
        void Init();
        void Render();
        void Update();
    };

}

#endif // BACKGROUNDS_H_INCLUDED
