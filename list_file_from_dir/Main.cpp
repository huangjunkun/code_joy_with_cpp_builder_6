//---------------------------------------------------------------------------

#include <vcl.h>

#include <stack>
using namespace std;

#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    TreeView1->MultiSelect = true;
    TreeView1->AutoExpand = false; //true
    TTreeNode*  node = new TTreeNode(TreeView1->Items);
    //TTreeNodes*  nodes = new TTreeNodes(TreeView1);
    TreeView1->Items->AddChildFirst(node ,"AddChildFirst");
    TreeView1->Items->AddChild(node ,"AddChild");
    //node->Parent = TreeView1->Items[0][0]; //[C++ Error] Main.cpp(26): E2247 'TTreeNode::Parent' is not accessible
    //TreeView1->Items[0].Add(node ,"Items[0].Add");
    TreeView1->Items->Add(TreeView1->Items[0][3] ,"Items[1]");
    //static_cast<TTreeNodes*>(TreeView1->Items[0][3])->AddChildFirst(node ,"Items[0][3]");
    //[C++ Error] Main.cpp(29): E2031 Cannot cast from 'TTreeNode *' to 'TTreeNodes *'
    TreeView1->Items->Insert(TreeView1->Items[0][5] ,"111111");
    delete  node;
    //delete  nodes;
}
//---------------------------------------------------------------------------
/*
  TTreeNode *Node1;
  TreeView1->Items->Clear(); // remove any existing nodes
  // Add a root node
  TreeView1->Items->Add(NULL, "RootNode1");

  // Set MyTreeNode to first node in tree view and add a child node to it
  Node1 = TreeView1->Items->Item[0];
  TreeView1->Items->AddChild(Node1,"ChildNode1");

  // Add another root node
  TreeView1->Items->Add(Node1, "RootNode2");

  // Reset Node1 to RootNode2 and add a child node to it
  Node1 = TreeView1->Items->Item[2];

  TreeView1->Items->AddChild(Node1,"ChildNode2");

  // Reset Node1 to ChildNode2 and add a child node to it
  Node1 = TreeView1->Items->Item[3];
  TreeView1->Items->AddChild(Node1,"ChildNode2a");

   //Add another child to ChildNode2 following ChildNode2a
  TreeView1->Items->AddChild(Node1,"ChildNode2b");
  // add another root node
  TreeView1->Items->Add(TreeView1->Items->Item[0], "RootTreeNode3");
 */
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
    ListBox1->Items->Clear();
    stack<String>   DirStack;
    DirStack.push(DirectoryListBox1->Directory);
    while(!DirStack.empty())
    {
        //ShowMessage("DirectoryListBox1->ItemIndex = "+String(DirectoryListBox1->ItemIndex));
        for(int i=DirectoryListBox1->ItemIndex+1; i<DirectoryListBox1->Count; i++)
        {
            DirStack.push(DirectoryListBox1->Directory+"\\"+DirectoryListBox1->Items->Strings[i]);
            //ShowMessage("DirStack.push()"+DirectoryListBox1->Items->Strings[i]);
        }
        //ListBox1->Items->AddStrings(FileListBox1->Items) ;
        for(int i=0; i<FileListBox1->Count; i++)
        {
            ListBox1->Items->Add(DirectoryListBox1->Directory+"\\"+FileListBox1->Items->Strings[i]);
        }
        //DirectoryListBox1->ItemIndex -= 1;
        DirectoryListBox1->Directory = DirStack.top();
        //ShowMessage("DirStack.top():"+DirStack.top()+" ,Directory :" +DirectoryListBox1->Directory);
        DirStack.pop();
        DirStack.pop();
    }
}
//---------------------------------------------------------------------------

