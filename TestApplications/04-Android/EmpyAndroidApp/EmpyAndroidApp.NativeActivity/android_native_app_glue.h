/*
 * Copyright (C) 2010 Das Android Open Source-Projekt
 *
 * Lizenziert unter der Apache-Lizenz, Version 2.0 ("Lizenz");
 * Sie d�rfen diese Datei nur gem�� den Lizenzbedingungen verwenden.
 * Eine Kopie der Lizenz erhalten Sie unter:
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Sofern nicht durch geltendes Recht anders festgelegt oder schriftlich vereinbart, wird
 * die unter der Lizenz vertriebene Software WIE BESEHEN,
 * OHNE GARANTIEN ODER BEDINGUNGEN GLEICH WELCHER ART, seien sie ausdr�cklich oder konkludent, zur Verf�gung gestellt.
 * Die unter der Lizenz geltenden Berechtigungen und Einschr�nkungen entnehmen Sie
 * der Lizenz in der jeweiligen Sprache.
 *
 */

#ifndef _ANDROID_NATIVE_APP_GLUE_H
#define _ANDROID_NATIVE_APP_GLUE_H

#include <poll.h>
#include <pthread.h>
#include <sched.h>

#include <android/configuration.h>
#include <android/looper.h>
#include <android/native_activity.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Die von <android/native_activity.h> bereitgestellte Schnittstelle f�r systemeigene Aktivit�ten
 * basiert auf einer Reihe von von Anwendungen bereitgestellten R�ckrufen, die 
 * vom Hauptthread der Anwendung aufgerufen werden, wenn bestimmte Ereignisse eintreten.
 *
 * Das bedeutet, dass keiner dieser R�ckrufe _blockieren_ _darf_, andernfalls
 * besteht die Gefahr, dass das System das Schlie�en der Anwendung erzwingt. Dieses
 * Programmiermodell ist direkt, unaufw�ndig, weist aber Einschr�nkungen auf.
 *
 * Mithilfe der statischen Bibliothek "threaded_native_app" kann ein anderes
 * Ausf�hrungsmodell bereitgestellt werden, bei dem die Anwendung ihre eigene Hauptereignisschleife
 * in einem anderen Thread implementieren kann. Das funktioniert so:
 *
 * 1/ Die Anwendung muss eine Funktion mit dem Namen "android_main()" bereitstellen,
 *    die beim Erstellen der Aktivit�t in einem neuen Thread, der sich
 *    vom Hauptthread der Aktivit�t unterscheidet, aufgerufen wird.
 *
 * 2/ android_main() empf�ngt einen Zeiger auf eine g�ltige "android_app"-Struktur,
 *    die Verweise auf andere wichtige Objekte enth�lt, z. B. die 
 *    ANativeActivity-Objektinstanz, in der die Anwendung ausgef�hrt wird.
 *
 * 3/ Das Objekt "android_app" enth�lt eine ALooper-Instanz, die bereits auf zwei wichtige
 *    Dinge lauscht:
 *
 *      - Lebenszyklusereignisse der Aktivit�t (z. B. "Anhalten", "Fortsetzen"). Siehe dazu unten die APP_CMD_XXX-
 *        Deklarationen.
 *
 *      - Eingabeereignisse, die aus der an die Aktivit�t angef�gte AInputQueue kommen.
 *
 *    Jede davon entsprechen einem ALooper-Bezeichner, der von
 *    ALooper_pollOnce mit den Werten LOOPER_ID_MAIN bzw. LOOPER_ID_INPUT
 *    zur�ckgegeben wird.
 *
 *    Ihre Anwendung kann den gleichen ALooper verwenden, um auf weitere
 *    Dateideskriptoren zu lauschen. Sie k�nnen entweder r�ckrufbasiert sein oder mit
 *    R�ckgabebezeichnern, die mit LOOPER_ID_USER beginnen.
 *
 * 4/ Immer, wenn Sie ein LOOPER_ID_MAIN- oder LOOPER_ID_INPUT-Ereignis empfangen,
 *    zeigen die zur�ckgegebenen Daten auf eine android_poll_source-Struktur. Sie k�nnen
 *    daf�r die Funktion "process()" aufrufen und "android_app->onAppCmd"
 *    sowie "android_app->onInputEvent" einsetzen, die dann f�r Ihre eigene Verarbeitung
 *    des Ereignisses aufgerufen werden.
 *
 *    Alternativ k�nnen Sie die Funktionen auf niederer Ebene aufrufen, um die
 *    Daten direkt zu verarbeiten... Beispiele f�r die Umsetzung finden Sie in den Implementierungen von
 *    "process_cmd()" und "process_input()" im Glue Code.
 *
 * Ein vollst�ndiges Syntaxbeispiel finden Sie im Beispiel mit dem Namen "native-activity",
 * das im NDK enthalten ist. Weitere Informationen finden Sie auch im JavaDoc von " NativeActivity".
 */

struct android_app;

/**
 * Einem ALooper fd zugeordnete Daten, die als die "outData" zur�ckgegeben
 * werden, wenn in der Quelle Daten bereit sind.
 */
struct android_poll_source {
    // Der Bezeichner dieser Quelle.  Das kann LOOPER_ID_MAIN oder
    // LOOPER_ID_INPUT sein.
    int32_t id;

    // Die android_app, der dieser ident zugeordnet ist.
    struct android_app* app;

    // Aufzurufende Funktion zum Durchf�hren der Standardverarbeitung von Daten aus
    // dieser Quelle.
    void (*process)(struct android_app* app, struct android_poll_source* source);
};

/**
 * Dies ist die Schnittstelle f�r den standardm��igen Verbindungscode einer
 * Threadanwendung. In diesem Modell wird der Code der Anwendung in einem
 * eigenen Thread getrennt vom Hauptthread des Prozesses ausgef�hrt.
 * Es ist nicht erforderlich, dass dieser Thread der Java
 * VM zugeordnet ist, obwohl das f�r JNI-Aufrufe von
 * Java-Objekten erforderlich ist.
 */
struct android_app {
    // Die Anwendung kann hier einen Zeiger auf ihr eigenes
    // Statusobjekt platzieren, wenn das erw�nscht ist.
    void* userData;

    // Setzen Sie hier die Funktion zum Verarbeiten von Befehlen der Haupt-App ein (APP_CMD_*)
    void (*onAppCmd)(struct android_app* app, int32_t cmd);

    // Setzen Sie hier die Funktion zum Verarbeiten von Eingabeereignissen ein. An diesem Punkt
    // wurde die Zuteilung des Ereignisses bereits vorbereitet und wird bei der
    // R�ckgabe abgeschlossen. Geben Sie 1 f�r verarbeitete Ereignisse, 0 f�r standardm��ige
    // Zuteilung zur�ck.
    int32_t (*onInputEvent)(struct android_app* app, AInputEvent* event);

    // Die ANativeActivity-Objektinstanz, in der diese App ausgef�hrt wird.
    ANativeActivity* activity;

    // Die aktuelle Konfiguration, in der die App ausgef�hrt wird.
    AConfiguration* config;

    // Die ist der gespeicherte Status der letzten Instanz, wie der zum Erstellungszeitpunkt �bergeben wird.
    // Er lautet NULL, wenn es keinen Status gab. Sie k�nnen dies bei Bedarf verwenden; der
    // Arbeitsspeicher bleibt erhalten, bis Sie "android_app_exec_cmd()" f�r
    // APP_CMD_RESUME aufrufen, wodurch er freigegeben und "savedState" auf NULL gesetzt wird.
    // Diese Variablen sollten nur bei der Verarbeitung eines APP_CMD_SAVE_STATE ge�ndert
    // werden und werden an diesem Punkt mit NULL initialisiert. Sie k�nnen dann einen malloc
    // des Status ausf�hren und die Informationen hier einsetzen. In diesem Fall wird der
    // Arbeitsspeicher sp�ter f�r Sie freigegeben.
    void* savedState;
    size_t savedStateSize;

    // Der dem Thread der App zugeordnete ALooper.
    ALooper* looper;

    // Bei einem anderen Wert als NULL ist dies die Eingabewarteschlange, aus der die App
    // Benutzereingabeereignisse empf�ngt.
    AInputQueue* inputQueue;

    // Bei einem anderen Wert als NULL ist dies die Fensteroberfl�che, auf der die App zeichnen kann.
    ANativeWindow* window;

    // Aktuelles Inhaltsrechteck des Fensters; dies ist der Bereich in dem der
    // Inhalt des Fensters platziert werden soll, damit der Benutzer ihn sehen kann.
    ARect contentRect;

    // Aktueller Status der Aktivit�t der App. Kann entweder APP_CMD_START,
    // APP_CMD_RESUME, APP_CMD_PAUSE oder APP_CMD_STOP sein; weitere Info unten.
    int activityState;

    // Dieser Wert ist nicht Null, wenn die NativeActivity der Anwendung
    // entfernt und auf den Abschluss des Threads der App gewartet wird.
    int destroyRequested;

    // -------------------------------------------------
    // Unten folgen "private" Implementierungen des Glue Codes.

    pthread_mutex_t mutex;
    pthread_cond_t cond;

    int msgread;
    int msgwrite;

    pthread_t thread;

    struct android_poll_source cmdPollSource;
    struct android_poll_source inputPollSource;

    int running;
    int stateSaved;
    int destroyed;
    int redrawNeeded;
    AInputQueue* pendingInputQueue;
    ANativeWindow* pendingWindow;
    ARect pendingContentRect;
};

enum {
    /**
     * Looper-Daten-ID von Befehlen, die aus dem Hauptthread der App stammen, der
     * als Bezeichner von "ALooper_pollOnce()" zur�ckgegeben wird. Die Daten f�r diesen
     * Bezeichner sind ein Zeiger auf eine android_poll_source-Struktur.
     * Diese k�nnen mit android_app_read_cmd() und android_app_exec_cmd()
     * abgerufen und bearbeitet werden.
     */
    LOOPER_ID_MAIN = 1,

    /**
     * Looper-Daten-ID von Ereignissen, die aus der AInputQueue des
     * Fensters der Anwendung kommen, das als Bezeichner von
     * ALooper_pollOnce() zur�ckgegeben wird. Die Daten f�r diesen Bezeichner sind ein Zeiger auf eine
     * android_poll_source-Struktur. Sie k�nnen �ber das inputQueue-Objekt
     * von android_app gelesen werden.
     */
    LOOPER_ID_INPUT = 2,

    /**
     * Start der benutzerdefinierten ALooper-Bezeichner.
     */
    LOOPER_ID_USER = 3,
};

enum {
    /**
     * Befehl aus dem Hauptthread: die AInputQueue hat sich ge�ndert. Bei der Verarbeitung
     * dieses Befehls wird android_app->inputQueue auf die neue Warteschlange
     * (oder NULL) aktualisiert.
     */
    APP_CMD_INPUT_CHANGED,

    /**
     * Befehl vom Hauptthread: Ein neues ANativeWindow ist bereit zur Nutzung. Beim
     * Empfang dieses Befehls enth�lt android_app->window die neue
     * Fensterfl�che.
     */
    APP_CMD_INIT_WINDOW,

    /**
     * Befehl vom Hauptthread: das vorhandene ANativeWindow muss beendet
     * werden. Beim Empfang dieses Befehls enth�lt android_app->window noch das
     * vorhandene Fenster und wird nach dem Aufruf von android_app_exec_cmd
     * auf NULL gesetzt.
     */
    APP_CMD_TERM_WINDOW,

    /**
     * Befehl vom Hauptthread: die Gr��e des aktuellen ANativeWindow wurde ge�ndert.
     * Bitte mit der neuen Gr��e neu zeichnen.
     */
    APP_CMD_WINDOW_RESIZED,

    /**
     * Befehl vom Hauptthread: das System muss das aktuelle ANativeWindow neu
     * zeichnen lassen. Sie sollten das Fenster neu zeichnen, bevor Sie dieses an
     * android_app_exec_cmd() �bergeben, um vor�bergehende Darstellungsfehler zu vermeiden.
     */
    APP_CMD_WINDOW_REDRAW_NEEDED,

    /**
     * Befehl vom Hauptthread: Der Inhaltsbereich des Fensters hat sich ge�ndert,
     * etwa durch Ein- oder Ausblenden des Bildschirm-Eingabefensters. Sie k�nnen
     * das neue Inhaltsrechteck in android_app::contentRect finden.
     */
    APP_CMD_CONTENT_RECT_CHANGED,

    /**
     * Befehl vom Hauptthread: Das Aktivit�tsfenster der App hat den
     * Eingabefokus erhalten.
     */
    APP_CMD_GAINED_FOCUS,

    /**
     * Befehl vom Hauptthread: Das Aktivit�tsfenster der App hat den
     * Eingabefokus verloren.
     */
    APP_CMD_LOST_FOCUS,

    /**
     * Befehl vom Hauptthread: Die aktuelle Ger�tekonfiguration hat sich ge�ndert.
     */
    APP_CMD_CONFIG_CHANGED,

    /**
     * Befehl vom Hauptthread: Das System hat wenig Arbeitsspeicher.
     * Versuchen Sie, die Speicherauslastung zu verringern.
     */
    APP_CMD_LOW_MEMORY,

    /**
     * Befehl vom Hauptthread: Die Aktivit�t der App wurde gestartet.
     */
    APP_CMD_START,

    /**
     * Befehl vom Hauptthread: Die Aktivit�t der App wurde wieder aufgenommen.
     */
    APP_CMD_RESUME,

    /**
     * Befehl vom Hauptthread: Die App sollte einen neuen gespeicherten Status
     * f�r sich generieren, um ihn bei Bedarf wiederherstellen zu k�nnen. Wenn Sie �ber einen gespeicherten Status verf�gen,
     * weisen Sie ihn mit malloc zu, und platzieren Sie ihn in android_app.savedState mit
     * der Gr��e in android_app.savedStateSize. Sie werden sp�ter f�r Sie
     * freigegeben.
     */
    APP_CMD_SAVE_STATE,

    /**
     * Befehl vom Hauptthread: die Aktivit�t der App wurde angehalten.
     */
    APP_CMD_PAUSE,

    /**
     * Befehl vom Hauptthread: Die Aktivit�t der App wurde beendet.
     */
    APP_CMD_STOP,

    /**
     * Befehl vom Hauptthread: Die Aktivit�t der App wird entfernt, und vor
     * dem Fortfahren wird auf das Aufr�umen und Schlie�en des Hauptthreads der App gewartet.
     */
    APP_CMD_DESTROY,
};

/**
 * Aufrufen, wenn ALooper_pollAll() LOOPER_ID_MAIN zur�ckgibt, Lesen der
 * n�chsten App-Befehlsnachricht.
 */
int8_t android_app_read_cmd(struct android_app* android_app);

/**
 * Aufrufen mit dem von android_app_read_cmd() zur�ckgegebenen Befehl, um
 * die anf�ngliche Vorverarbeitung des angegebenen Befehls auszuf�hren. Sie k�nnen nach dem Aufrufen dieser Funktion
 * eigene Aktionen f�r den Befehl ausf�hren.
 */
void android_app_pre_exec_cmd(struct android_app* android_app, int8_t cmd);

/**
 * Aufrufen mit dem von android_app_read_cmd() zur�ckgegebenen Befehl, um die
 * abschlie�ende Nachverarbeitung des angegebenen Befehls auszuf�hren. Sie m�ssen Ihre eigenen Aktionen f�r den
 * Befehl vor dem Aufrufen dieser Funktion ausgef�hrt haben.
 */
void android_app_post_exec_cmd(struct android_app* android_app, int8_t cmd);

/**
 * Dies ist die Funktion, die der Anwendungscode implementieren muss, er
 * stellt den Haupteinsprungspunkt der App dar.
 */
extern void android_main(struct android_app* app);

#ifdef __cplusplus
}
#endif

#endif /* _ANDROID_NATIVE_APP_GLUE_H */
