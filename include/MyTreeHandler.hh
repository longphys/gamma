#ifndef MyTreeHandler_hh
#define MyTreeHandler_hh

#include "G4Types.hh"

#include "TFile.h"
#include "TTree.h"

class MyTreeHandler
{
    public: 
        MyTreeHandler(const MyTreeHandler& aTreeHandler) = delete;
        static MyTreeHandler* GetInstance()
        {
            if (fTreeHandlerPtr == NULL)
            {
                fTreeHandlerPtr = new MyTreeHandler();
                return fTreeHandlerPtr;
            }
            else
            {
                return fTreeHandlerPtr;
            }
        }
        G4int Push(int64_t eventNr, G4double dE, int64_t comptNr, G4double backEDep);
        G4int Open();
        G4int Close();
        G4int Print();

    protected:
        static MyTreeHandler* fTreeHandlerPtr;

        MyTreeHandler();

        TFile* fFile;
        TTree* fTree;
        int64_t fEventNr;

        G4double fdE, fbackEDep;
        
        int64_t fcomptNr;
        
};

#endif
