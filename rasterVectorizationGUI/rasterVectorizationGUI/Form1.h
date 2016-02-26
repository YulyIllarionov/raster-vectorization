#pragma once

#include "VectorizationDll.h"
#include <msclr\marshal_cppstd.h>
//#include "base_types.h"

namespace rasterVectorizationGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
    using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::PictureBox^  rasterImageBox;
    protected: 

    protected: 
    private: System::Windows::Forms::Button^  loadButton;
    private: System::Windows::Forms::Button^  saveButton;
    private: System::Windows::Forms::OpenFileDialog^  openFileDialog;

    private: System::Windows::Forms::Button^  searchButton;


    private: System::ComponentModel::IContainer^  components;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->rasterImageBox = (gcnew System::Windows::Forms::PictureBox());
            this->loadButton = (gcnew System::Windows::Forms::Button());
            this->saveButton = (gcnew System::Windows::Forms::Button());
            this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
            this->searchButton = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rasterImageBox))->BeginInit();
            this->SuspendLayout();
            // 
            // rasterImageBox
            // 
            this->rasterImageBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
                | System::Windows::Forms::AnchorStyles::Left) 
                | System::Windows::Forms::AnchorStyles::Right));
            this->rasterImageBox->Location = System::Drawing::Point(12, 12);
            this->rasterImageBox->Name = L"rasterImageBox";
            this->rasterImageBox->Size = System::Drawing::Size(410, 312);
            this->rasterImageBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
            this->rasterImageBox->TabIndex = 0;
            this->rasterImageBox->TabStop = false;
            // 
            // loadButton
            // 
            this->loadButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
            this->loadButton->Location = System::Drawing::Point(438, 242);
            this->loadButton->Name = L"loadButton";
            this->loadButton->Size = System::Drawing::Size(110, 23);
            this->loadButton->TabIndex = 1;
            this->loadButton->Text = L"Load Image";
            this->loadButton->UseVisualStyleBackColor = true;
            this->loadButton->Click += gcnew System::EventHandler(this, &Form1::loadButton_Click);
            // 
            // saveButton
            // 
            this->saveButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
            this->saveButton->Location = System::Drawing::Point(438, 300);
            this->saveButton->Name = L"saveButton";
            this->saveButton->Size = System::Drawing::Size(110, 24);
            this->saveButton->TabIndex = 2;
            this->saveButton->Text = L"Save Image";
            this->saveButton->UseVisualStyleBackColor = true;
            // 
            // openFileDialog
            // 
            this->openFileDialog->Filter = L"BMP Files (*.bmp)|*.bmp|JPEG Files (*.jpeg)|*.jpeg|PNG Files (*.png)|*.png|JPG Fi" 
                L"les (*.jpg)|*.jpg";
            this->openFileDialog->Title = L"Load Image";
            this->openFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog_FileOk);
            // 
            // searchButton
            // 
            this->searchButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
            this->searchButton->Location = System::Drawing::Point(438, 271);
            this->searchButton->Name = L"searchButton";
            this->searchButton->Size = System::Drawing::Size(110, 23);
            this->searchButton->TabIndex = 3;
            this->searchButton->Text = L"Find Lines ";
            this->searchButton->UseVisualStyleBackColor = true;
            this->searchButton->Click += gcnew System::EventHandler(this, &Form1::searchButton_Click);
            // 
            // Form1
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(560, 336);
            this->Controls->Add(this->searchButton);
            this->Controls->Add(this->saveButton);
            this->Controls->Add(this->loadButton);
            this->Controls->Add(this->rasterImageBox);
            this->MinimumSize = System::Drawing::Size(500, 350);
            this->Name = L"Form1";
            this->Text = L"Form1";
            this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rasterImageBox))->EndInit();
            this->ResumeLayout(false);

        }
#pragma endregion

    
    //User variables
    private: 
        Image^ rasterImageForDraw;
        Image^ rasterImageForDrawTemp;
        array<TrackBar ^> ^ linesParams;
        APP_NAMESPACE::Vectorization* f_vectorization;
        std::vector<std::pair<std::vector<std::pair<int, int>>, int>>* f_lines;

    private: void drawSupportPoints(void)
    {
        delete rasterImageForDrawTemp; //just in case
        rasterImageForDrawTemp = (Image^)rasterImageForDraw->Clone();
        Graphics^ graphics = Graphics::FromImage(rasterImageForDrawTemp);
        for (int i = 0; i < f_lines->size(); i++)
        {
            int size = (*f_lines).at(i).first.size();
            int scale = (int)(*f_lines).at(i).second;
            for (int j = 0; j < size; j += scale)
            {
                int radius = 4;
                int x = (*f_lines).at(i).first.at(j).first - radius;
                int y = (*f_lines).at(i).first.at(j).second - radius;
                graphics->FillEllipse(gcnew SolidBrush(Color::Red), x, y, radius * 2, radius * 2);
            }
        }
        rasterImageBox->Image = rasterImageForDrawTemp;
    }

    private: System::Void loadButton_Click(System::Object^  sender, System::EventArgs^  e) 
             {
                 if ( openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK )
                 {
                     if ( openFileDialog->FileName != String::Empty)
                     {
                         f_vectorization = new APP_NAMESPACE::Vectorization(msclr::interop::marshal_as<std::string>(openFileDialog->FileName));
                         f_lines = new std::vector<std::pair<std::vector<std::pair<int, int>>, int>>(f_vectorization->GetLines());
                         rasterImageForDraw = Image::FromFile( openFileDialog->FileName );
                         rasterImageBox->Image = rasterImageForDraw; //dynamic_cast<Image^>(rasterImageForDraw);
                         IntPtr ptrToFileName = Marshal::StringToHGlobalAnsi(openFileDialog->FileName);
                         char* fileName = static_cast<char*>(ptrToFileName.ToPointer());
                     }
                 }
             }
    private: System::Void openFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
             }
    private: System::Void searchButton_Click(System::Object^  sender, System::EventArgs^  e) 
            {
                delete linesParams; //just in case
                linesParams = gcnew array< TrackBar^ >(f_lines->size());
                for (int i = 0; i<f_lines->size(); i++)
                {
                    linesParams[i] = gcnew TrackBar();
                    linesParams[i]->ValueChanged += gcnew System::EventHandler(this, &Form1::trackBar_ValueChanged);

                    linesParams[i]->Name = System::Convert::ToString(i);

                    linesParams[i]->Minimum = 10;
                    linesParams[i]->Maximum = f_lines->at(i).first.size() - 1;
                    linesParams[i]->Value = linesParams[i]->Minimum;

                    linesParams[i]->Width = loadButton->Width;
                    linesParams[i]->Height = loadButton->Height;
                    linesParams[i]->Left = loadButton->Left;
                    linesParams[i]->Top = rasterImageBox->Top + i * 2 * loadButton->Height;
                    linesParams[i]->Width = loadButton->Width;
                    linesParams[i]->Height = loadButton->Height;
                    linesParams[i]->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);
                    this->Controls->Add(linesParams[i]);
                }
                int height = loadButton->Height * 2 * (f_lines->size() + 3);
                if (this->Height < height)
                    this->Height = height;
                drawSupportPoints();
            }
    private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e) 
             {
             }
    private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
             {
             }
    private: System::Void trackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e)
             {
                 TrackBar ^ changedTrackBar = (TrackBar ^)sender;
                 int index = System::Convert::ToInt32(changedTrackBar->Name);
                 f_lines->at(index).second = changedTrackBar->Value;
                 drawSupportPoints();
             }
};
}

