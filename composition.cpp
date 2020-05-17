#include "composition.h"

#include <QXmlStreamWriter>
#include <QtXmlPatterns>
#include <QMessageBox>


Composition::Composition(fsmVector fsms, linkVector links)
     : fsms_(fsms), links_(links)
{

}

fsmVector Composition::getFsms() const
{
     return fsms_;
}

linkVector Composition::getLinks() const
{
     return links_;
}

QStringList Composition::getChannels(const QString &filePath) const
{
     QFile file(filePath);
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         Q_ASSERT(false);
     }

     QTextStream in(&file);
     in.readLine();
     auto inputsString = in.readLine();
     inputsString.remove(0, 8);
     return inputsString.split(" ");
}

void Composition::formBalm2Script() const
{
     fsmVector myFSMs = getFsms();
     if (myFSMs.size() != 2)
     {
          qDebug() << "we need 2 components...";
          return;
     }

     QFile script("script.sh");
     if (!script.open(QIODevice::WriteOnly))
     {
          return;
     }
     QTextStream toScript(&script);

     QString filePath1 = myFSMs[0].getFullPath();
     QString fileName1 = myFSMs[0].getFileName();
     QString filePath2 = myFSMs[1].getFullPath();
     QString fileName2 = myFSMs[1].getFileName();

     Q_ASSERT(!filePath1.isEmpty());
     Q_ASSERT(!fileName1.isEmpty());
     Q_ASSERT(!filePath2.isEmpty());
     Q_ASSERT(!fileName2.isEmpty());

     linkVector myLinks = getLinks();

     QStringList channels1, channels2;
     channels1 = getChannels( filePath1 );
     channels2 = getChannels( filePath2 );

     QString channels1_inp, channels1_out, channels2_inp, channels2_out, ext_channel_input_1, ext_channel_output_1, ext_channel_input_2, ext_channel_output_2;
     QStringList oldNamesInp, oldNamesOut; // Внешние для композиции каналы
     int E_number=0;
     for (size_t i = 0; i < myLinks.size(); i++)
     {
          if (myLinks[i].getInputFsm().getName() == myFSMs[0].getName())
          {
               channels1_inp += myLinks[i].getId();
               channels1_inp += '|';
               if ( myLinks[i].getOutputFsm().getName()=="" )
               {
                    //ext_channel2 += "E" + QString::number(E_number)+',';
                    ext_channel_input_2 += myLinks[i].getId() + ',';
                    oldNamesInp.push_back(myLinks[i].getId());
               }
               E_number++;
          }

          if ( myLinks[i].getOutputFsm().getName() == myFSMs[0].getName() )
          {
               channels1_out += myLinks[i].getId();
               channels1_out += '|';
               if ( myLinks[i].getInputFsm().getName() == "" )
               {
                    //ext_channel2 += "E" + QString::number(E_number) + ',';
                    ext_channel_output_2 += myLinks[i].getId() + ',';
                    oldNamesOut.push_back(myLinks[i].getId());
               }
               E_number++;
          }

          if ( myLinks[i].getInputFsm().getName() == myFSMs[1].getName() )
          {
               channels2_inp += myLinks[i].getId();
               channels2_inp += '|';
               if ( myLinks[i].getOutputFsm().getName() == "" )
               {
                    //ext_channel1 += "E" + QString::number(E_number) + ',';
                    ext_channel_input_1 += myLinks[i].getId() + ',';
                    oldNamesInp.push_back(myLinks[i].getId());
               }
               E_number++;
          }

          if (myLinks[i].getOutputFsm().getName() == myFSMs[1].getName())
          {
               channels2_out += myLinks[i].getId();
               channels2_out += '|';
               if (myLinks[i].getInputFsm().getName()=="")
               {
                    //ext_channel1 += "E" + QString::number(E_number) + ',';
                    ext_channel_output_1 += myLinks[i].getId() + ',';
                    oldNamesOut.push_back(myLinks[i].getId());
               }
               E_number++;
          }
     }

     channels1_out.remove(channels1_out.size() - 1, 1);
     channels2_out.remove(channels2_out.size() - 1, 1);
     ext_channel_input_1.remove(ext_channel_input_1.size() - 1, 1);
     ext_channel_output_1.remove(ext_channel_output_1.size() - 1, 1);
     ext_channel_input_2.remove(ext_channel_input_2.size() - 1, 1);
     ext_channel_output_2.remove(ext_channel_output_2.size() - 1, 1);

     auto addPrefix = [](const QString& name, const QString& preffix){
          return preffix + name;
     };

     const static QString balm("balm -c ");
     const static QString quote("\"");
     QString polyname1 = addPrefix(fileName1, "poly");
     QString polyname2 = addPrefix(fileName2, "poly");
     QString syncname1 = addPrefix(polyname1, "sync");
     QString syncname2 = addPrefix(polyname2, "sync");
     QString expname1 = addPrefix(syncname1, "exp");
     QString expname2 = addPrefix(syncname2, "exp");
     QString supExtName1 = addPrefix(expname1, "sup");
     QString supExtName2 = addPrefix(expname2, "sup");

     auto getExpansion = [&ext_channel_input_1, &ext_channel_output_1, &ext_channel_input_2, &ext_channel_output_2, syncname1, syncname2, &expname1, &expname2] ()
     {
          QString expCommand1, expCommand2;
          if(!ext_channel_input_2.isEmpty() && !ext_channel_output_2.isEmpty())
          {
               expCommand2 = balm + quote + "expansion " + ext_channel_input_2 + "," + ext_channel_output_2 + " " + syncname2 + " " + expname2 + quote;

          }
          else if( !ext_channel_input_2.isEmpty() )
          {
               expCommand2 = balm + quote + "expansion " + ext_channel_input_2 + " " + syncname2 + " " + expname2 + quote;
          }
          else if( !ext_channel_output_2.isEmpty() )
          {
               expCommand2 = balm + quote + "expansion " + ext_channel_output_2 + " " + syncname2 + " " + expname2 + quote;
          }
          else
          {
               expname2 = syncname2;
          }
          if( !ext_channel_input_1.isEmpty() && !ext_channel_output_1.isEmpty() )
          {
               expCommand1 = balm + quote + "expansion " + ext_channel_input_1 + "," + ext_channel_output_1 + " " + syncname1 + " " + expname1 + quote;
          }
          else if( !ext_channel_input_1.isEmpty() )
          {
               expCommand1 = balm + quote + "expansion " + ext_channel_input_1 + " " + syncname1 + " " + expname1 + quote;
          }
          else if( !ext_channel_output_1.isEmpty() )
          {
               expCommand1 = balm + quote + "expansion " + ext_channel_output_1 + " " + syncname1 + " " + expname1 + quote;
          }
          else
          {
               expname1 = syncname1;
          }

          return expCommand1 + "\n" + expCommand2;
     };

     auto getExtChannels = [ext_channel_input_1, ext_channel_output_1, ext_channel_input_2, ext_channel_output_2](){
          QString result;
          if(!ext_channel_input_1.isEmpty())
          {
               result += ext_channel_input_1;
          }
          if( !ext_channel_input_2.isEmpty() )
          {
               if( !result.isEmpty() )
               {
                    result += "," + ext_channel_input_2;
               }
               else {
                    result += ext_channel_input_2;
               }
          }
          if( !ext_channel_output_1.isEmpty() )
          {
               if( !result.isEmpty() )
               {
                    result += "," + ext_channel_output_1;
               }
               else {
                    result += ext_channel_output_1;
               }
          }
          if( !ext_channel_output_2.isEmpty() )
          {
               if( !result.isEmpty() )
               {
                    result += "," + ext_channel_output_2;
               }
               else {
                    result += ext_channel_output_2;
               }
          }
          return result;
     };

     auto getFormatedExtChannels = []( const QStringList& ext_chan_input_1, const QStringList& ext_chan_input_2,
                                       const QStringList& ext_chan_output_1, const QStringList& ext_chan_output_2 )
     {
          QString ext_chans;
          if( !ext_chan_input_1.isEmpty() )
          {
               ext_chans += ext_chan_input_1.join("|");
          }
          if( !ext_chan_input_2.isEmpty() )
          {
               if( !ext_chans.isEmpty() )
               {
                    ext_chans += "|" + ext_chan_input_2.join("|");
               }
               else {
                    ext_chans += ext_chan_input_2.join("|");
               }
          }
          if( !ext_chan_output_1.isEmpty() )
          {
               if( !ext_chans.isEmpty() )
               {
                    ext_chans += "|" + ext_chan_output_1.join("|");
               }
               else {
                    ext_chans += ext_chan_output_1.join("|");
               }
          }
          if( !ext_chan_output_2.isEmpty() )
          {
               if( !ext_chans.isEmpty() )
               {
                    ext_chans += "|" + ext_chan_output_2.join("|");
               }
               else {
                    ext_chans += ext_chan_output_2.join("|");
               }
          }
          return ext_chans;
     };

     QStringList oldNames = oldNamesInp + oldNamesOut;

     QString read_para1 = balm + quote + "read_para_fsm " + channels1.join("|")  + " " + filePath1 + " " + polyname1 + quote;
     QString read_para2 = balm + quote + "read_para_fsm " + channels2.join("|")  + " " + polyname2 + quote;
     QString chan_sync = "error";
     QString product = "error";
     QString suportExp = "error";
     QString expansion = getExpansion();
     if( channels2.size() >= channels1.size() )
     {
          chan_sync = balm + quote + "chan_sync " + channels2.join("|") + "|E " + channels1.join("|") + "|E  " + polyname2 + " " + polyname1 + " " + syncname2 + " " + syncname1 + quote;
          auto alphabetSize = channels2.size();
          suportExp = balm + quote + "support " + channels2.join(",") + ",E(" + QString::number(alphabetSize) + ") " + expname1 + " " + supExtName1 + quote;
          product = balm + quote + "product " + expname2 + " " + /*expname1*/ supExtName1 + " pro.aut" + quote;

     }
     else
     {
          chan_sync = balm + quote + "chan_sync " + channels1.join("|") + "|E " + channels1.join("|") + "|E  " + polyname1 + " " + polyname2 + " " + syncname1 + " " + syncname2 + quote;
          auto alphabetSize = channels1.size();
          suportExp = balm + quote + "support " + channels1.join(",") + ",E(" + QString::number( alphabetSize ) + ") " + expname2 + " " + supExtName2 + quote;
          product = balm + quote + "product " + expname1 + " " + /*expname2*/supExtName2 + " pro.aut" + quote;
     }
     QString restriction = balm + quote + "restriction " + getExtChannels() + " pro.aut" + " restr.aut" + quote;
     QString support_restr = balm + quote + "support " + oldNames.join(",") + ",E("+ QString::number(oldNames.size()) + ") restr.aut supp.aut" + quote;
     QStringList ext_chan_input_1 = ( ext_channel_input_1 != "" ) ? ext_channel_input_1.split(",") : QStringList();
     QStringList ext_chan_input_2 = ( ext_channel_input_2 != "" ) ? ext_channel_input_2.split(",") : QStringList();
     QStringList ext_chan_output_1 = ( ext_channel_output_1 != "" ) ? ext_channel_output_1.split(",") : QStringList();
     QStringList ext_chan_output_2 = ( ext_channel_output_2 != "" ) ? ext_channel_output_2.split(",") : QStringList();
     QString ext_chans = getFormatedExtChannels( ext_chan_input_1, ext_chan_input_2, ext_chan_output_1, ext_chan_output_2 );
     QString write_para = balm + quote + "write_para_fsm " + oldNames.join("|") + "|E " + ext_chans + " supp.aut fsm.aut" + quote;

     QString pyEditScript = "python3 main.py " + polyname1 + " " + syncname1 + " " + polyname2 + " " + syncname2;
     QString editedScriptStart = "sh edited_script.sh";
     QString scriptStopper = "exit 25";

     toScript << read_para1 << "\n" << read_para2 << "\n" << chan_sync << "\n" << pyEditScript << "\n" << editedScriptStart << "\n" <<
                 scriptStopper << "\n" << expansion << "\n" << suportExp << "\n" << product << "\n" << restriction << "\n" <<
                 support_restr << "\n" << write_para;

     script.close();
}

void Composition::formXmlFile() const
{
     QFile xmlCompositionFile("composition.xml");
     xmlCompositionFile.open(QIODevice::WriteOnly);

     QXmlStreamWriter xmlWriter(&xmlCompositionFile);
     xmlWriter.setAutoFormatting(true);
     xmlWriter.writeStartDocument();

     auto isExternal = [](const Fsm& fsm)
     {
          return ( ( "" == fsm.getName() ) && ( "" == fsm.getName() ) );
     };

     auto writeFsmInfo = [&xmlWriter, &isExternal](const Fsm& fsm)
     {
          if(isExternal(fsm))
          {
               xmlWriter.writeAttribute("type", "external");
          }
          else
          {
               xmlWriter.writeAttribute("type", "internal");
               xmlWriter.writeAttribute("id_comp", fsm.getName());
          }
     };

     xmlWriter.writeStartElement("start");

     xmlWriter.writeStartElement("composition"); // <composition>
     for(const auto& fsm : fsms_)
     {
          xmlWriter.writeStartElement("FSM");
          xmlWriter.writeAttribute("name", fsm.getName());
          xmlWriter.writeAttribute("id", fsm.getName());
          xmlWriter.writeEndElement(); //</FSM>
     }
     xmlWriter.writeEndElement(); // </composition>

     xmlWriter.writeStartElement("channels");
     xmlWriter.writeAttribute("num", QString::number(links_.size()));
     for(const auto& link : links_)
     {
          xmlWriter.writeStartElement("channel"); // <channel>
          xmlWriter.writeAttribute("id", link.getId());

          xmlWriter.writeStartElement("input");
          Fsm inputFsm = link.getInputFsm();
          writeFsmInfo(inputFsm);
          xmlWriter.writeEndElement(); // </input>

          xmlWriter.writeStartElement("output");
          Fsm outputFsm = link.getOutputFsm();
          writeFsmInfo(outputFsm);
          xmlWriter.writeEndElement();

          xmlWriter.writeEndElement(); // </channel>
     }
     xmlWriter.writeEndElement();// </channels>

     xmlWriter.writeEndElement();// </start>

     xmlWriter.writeEndDocument();// XML END
     xmlCompositionFile.close();
}


